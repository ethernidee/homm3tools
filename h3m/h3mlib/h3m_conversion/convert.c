// Created by John Åkerblom 2014-01-22

#include "../h3mlib.h"
#include "../h3m_creature.h"
#include "../h3m_object_categories.h"

#include "../default_od_body.h"
#include "../h3mlib_ctx.h"
#include "../h3mlib_cleanup.h"

#include "../meta/meta_push_od.h"
#include "../h3m_structures/h3m_oa.h"

// Currently creature conversion is only done for creatures inside objects
// TODO also convert creature objects on the map
#include "conv_tables_creatures.h"

#define MAX_CREATURES 7

#ifdef _WIN32
#include <windows.h>            // MAX_PATH
#else
#include <linux/limits.h>
#define MAX_PATH PATH_MAX
#endif

#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifdef _MSC_VER
#define snprintf _snprintf
#endif

#define FORMAT_ANY -1

#define PREFIX_SOD "[SoD] "
#define PREFIX_AB "[AB] "
#define PREFIX_WOG "[WoG] "
#define PREFIX_UNKNOWN ""
#define SUFFIX_DESC " [h3minternals.net] converted to RoE with h3mlib by potmdehex"

struct OA_HASH {
    int oa_index_in;            // key
    int oa_index_out;
    int body_size_delta;
    int convert_binary_compatible;
    UT_hash_handle hh;
};

struct CONV_CTX {
    struct OA_HASH *oa_hash;
    uint8_t impassable[2][255][255];    // Some maps are bigger than H3M_MAX_SIZE
    FILE *f_log_critical;
    FILE *f_log_warning;
    FILE *f_log_info;
    int last_hero_type;
};

enum LOG_LEVEL {
    LOG_CRITICAL,
    LOG_WARNING,
    LOG_INFO
};

// TODO could use standard format string style log
static void _log_msg(struct CONV_CTX *conv, int log_level, const char *msg)
{
    FILE *f = NULL;
#if 1
    switch (log_level) {
    case LOG_CRITICAL:
        f = conv->f_log_critical;
        break;
    case LOG_WARNING:
        f = conv->f_log_warning;
        break;
    case LOG_INFO:
        f = conv->f_log_info;
        break;
    default:
        return;
    }

    if (NULL != f) {
        fwrite(msg, strlen(msg), 1, f);
    }
#endif
}

static void _conv_init(struct CONV_CTX *conv, const char *log_name)
{
    char filename[MAX_PATH] = { 0 };

    if (NULL == log_name) {
        log_name = "default";
    }
    // Logging is very dirty right now, TODO revamp
#if 1
#ifdef _WIN32
    CreateDirectoryA("conv_logs", NULL);
#endif  /* _WIN32 */
    _snprintf(filename, sizeof(filename) - 1, "conv_logs\\%s_log_critical.txt",
        log_name);
    conv->f_log_critical = fopen(filename, "wb");
    _snprintf(filename, sizeof(filename) - 1, "conv_logs\\%s_log_warning.txt",
        log_name);
    conv->f_log_warning = fopen(filename, "wb");
    _snprintf(filename, sizeof(filename) - 1, "conv_logs\\%s_log_info.txt",
        log_name);
    conv->f_log_info = fopen(filename, "wb");
#endif
}

static void _conv_exit(struct CONV_CTX *conv)
{
    struct OA_HASH *cur = NULL;
    struct OA_HASH *tmp = NULL;

    HASH_ITER(hh, conv->oa_hash, cur, tmp) {
        HASH_DEL(conv->oa_hash, cur);
        free(cur);
    }

#if 1
    if (NULL != conv->f_log_critical) {
        fclose(conv->f_log_critical);
    }
    if (NULL != conv->f_log_warning) {
        fclose(conv->f_log_warning);
    }
    if (NULL != conv->f_log_info) {
        fclose(conv->f_log_info);
    }
#endif
}

// Hack way of including, TODO do properly
// hash function generated by mph residing in src\gen\defs.c
extern int def_bodies_hash(const char *);
#include "../gen/def_bodies_array.h"

static int _oa_type_from_def(const char *def)
{
    unsigned int val = 0;
    char def_lower[16] = { 0 };
    char *p = def_lower;

    // It's ofc bad to do this downcasing all the time
    // TODO stop downcasing 24/7
    strncpy(def_lower, def, sizeof(def_lower) - 1);
    for (; *p; ++p)
        *p = (char)tolower((int)*p);
    def = def_lower;

    // Standard def check
    if (-1 == (val = def_bodies_hash(def))) {
        return -1;
    } else if (val >= sizeof(def_bodies_array) / sizeof(void *)) {
        return -1;
    } else if (0 != strcmp(def_bodies_array[val], def)) {
        return -1;
    }

    return val;
}

// Here is a hack for adjusting object categorization to make sure non-RoE objects are marked as such
// It's all a dirty hack so TODO remove it when better version handling is had.
static int _oa_type_version_adjust(int meta_type, const char *def,
    uint32_t object_number)
{
    int val = 0;

    switch (meta_type) {
    case H3M_OBJECT_ARTIFACT:
        // Greatest RoE artifact is Orb of Inhibition at 126 TODO make define
        meta_type =
            (object_number >
            126) ? H3M_OBJECT_ARTIFACT_SOD : H3M_OBJECT_ARTIFACT;
        break;
        /*case H3M_OBJECT_DWELLING:
           meta_type = (H3M_OBJECT_DWELLING == _oa_type_from_def(def)) ? H3M_OBJECT_DWELLING : H3M_OBJECT_DWELLING_ABSOD;
           break; */
    case H3M_OBJECT_TOWN:
        // Greatest town is Fortress at 7 TODO make define
        meta_type =
            (object_number > 7) ? H3M_OBJECT_TOWN_ABSOD : H3M_OBJECT_TOWN;
        break;
    case H3M_OBJECT_DWELLING:
        // Greatest RoE Dwelling is Swordsman dwelling at 58 (TODO verify)  TODO make define
        meta_type =
            (object_number >
            58) ? H3M_OBJECT_DWELLING_ABSOD : H3M_OBJECT_DWELLING;
        break;
    case H3M_OBJECT_MONSTER:
        // Greatest RoE monster value is Diamond Golem at 117 TODO make define
        meta_type =
            (object_number >
            117) ? H3M_OBJECT_MONSTER_ABSOD : H3M_OBJECT_MONSTER;
        break;
        //case H3M_OBJECT_MONOLITH_TWO_WAY:
        //return (H3M_OBJECT_MONOLITH_TWO_WAY == _oa_type_from_def(def)) ? H3M_OBJECT_MONOLITH_TWO_WAY : H3M_OBJECT_MONOLITH_TWO_WAY_ABSOD;
    default:
        break;
    }

    // TODO don't mark WoG/other mods as ABSOD

    return meta_type;
}

static int _convert_oa_roe(struct H3MLIB_CTX *ctx_in,
    struct H3MLIB_CTX *ctx_out, struct CONV_CTX *conv)
{
    size_t max_count = ctx_in->h3m.oa.count;
    size_t count = 0;
    enum H3M_OBJECT oa_type = 0;
    struct H3M_OA_ENTRY *entry_in = NULL;
    struct META_OA_ENTRY *meta_in = NULL;
    struct H3M_OA_ENTRY *entry_out = NULL;
    struct OA_HASH *entry_conv = NULL;
    unsigned int i = 0;
    int body_size_delta = 0;
    int convert_binary_compatible = 0;

    if (NULL != ctx_out->h3m.oa.entries) {
        for (i = 0; i < ctx_out->h3m.oa.count; ++i) {
            if (NULL != ctx_out->h3m.oa.entries[i].header.def) {
                free(ctx_out->h3m.oa.entries[i].header.def);
            }
        }
        free(ctx_out->h3m.oa.entries);
    }
    ctx_out->h3m.oa.entries = calloc(max_count, sizeof(*(entry_out)));

    for (i = 0; i < max_count; ++i) {
        body_size_delta = 0;
        convert_binary_compatible = 0;
        entry_in = &ctx_in->h3m.oa.entries[i];
        meta_in = &ctx_in->meta.oa_entries[i];
        entry_out = &ctx_out->h3m.oa.entries[count];
        // TODO remove this version adjust hack
        oa_type =
            _oa_type_version_adjust(meta_in->type, entry_in->header.def,
            entry_in->body.object_number);

        switch (oa_type) {
        case -1:
            continue;
            // ABSOD objects to drop
        case H3M_OBJECT_PLACEHOLDER_HERO:      // TODO convert to random hero
        case H3M_OBJECT_ABANDONED_MINE_ABSOD:
        case H3M_OBJECT_ARTIFACT_AB:
        case H3M_OBJECT_ARTIFACT_SOD:
        case H3M_OBJECT_DWELLING_ABSOD:
        case H3M_OBJECT_GARRISON_ABSOD:
        case H3M_OBJECT_GENERIC_IMPASSABLE_TERRAIN_ABSOD:      // Not handled here
        case H3M_OBJECT_GENERIC_PASSABLE_TERRAIN_SOD:
        case H3M_OBJECT_GENERIC_VISITABLE_ABSOD:
        case H3M_OBJECT_RANDOM_DWELLING_ABSOD:
        case H3M_OBJECT_RANDOM_DWELLING_PRESET_LEVEL_ABSOD:
        case H3M_OBJECT_RANDOM_DWELLING_PRESET_ALIGNMENT_ABSOD:
        case H3M_OBJECT_QUEST_GUARD:   // Should be renamed with _ABSOD at end
        case H3M_OBJECT_SEERS_HUT:     // Simply drop for now... Vastly different in RoE with main problem being the other quest types
            continue;
        case H3M_OBJECT_WITCH_HUT:     // No skill customization for RoE Witch Hut
            body_size_delta = -4;
            break;
        case H3M_OBJECT_GARRISON:      // Garrisons are the only binary compatible objects that need conversion
            convert_binary_compatible = 1;
            break;
        case H3M_OBJECT_MONSTER_ABSOD:
            if (entry_out->body.object_number >=
                sizeof(creature_type_conv_table_roe) /
                sizeof(creature_type_conv_table_roe[0])) {
                continue;
            }
            break;
        default:
            break;
        }

        entry_out->header.def =
            (uint8_t *)strdup((char *)entry_in->header.def);
        entry_out->header.def_size = strlen((char *)entry_out->header.def);
        memcpy(&entry_out->body, &entry_in->body, sizeof(entry_out->body));

#if 1
        // WoG objects get thrown away here. TODO proper conversion, it's not that hard to convert
        // a lot of objects if there are hash maps in place (e.g WoG treasure chest -> normal treasure
        // chest etc)
        if (-1 == _oa_type_from_def(entry_in->header.def)) {
            free(entry_out->header.def);
            entry_out->header.def_size = sizeof("AVWmrnd0.def");
            entry_out->header.def = malloc(entry_out->header.def_size);
            _snprintf(entry_out->header.def, entry_out->header.def_size, "%s",
                "AVWmrnd0.def");
        }
#endif

        if (H3M_OBJECT_MONSTER_ABSOD == oa_type) {
            entry_out->body.object_number =
                (uint32_t) creature_type_conv_table_roe[entry_out->body.
                object_number];

            free(entry_out->header.def);
            entry_out->header.def_size = sizeof("AVWmrnd0.def");
            entry_out->header.def = malloc(entry_out->header.def_size);
            _snprintf(entry_out->header.def, entry_out->header.def_size, "%s",
                "AVWmrnd0.def");
        }
        // Conflux hack, Conflux->Random Town
        else if (H3M_OBJECT_TOWN_ABSOD == oa_type) {
            _snprintf(entry_out->header.def, entry_out->header.def_size, "%s",
                "AVCranx0.def");
            entry_out->body.object_class = 0x4D;
            entry_out->body.object_number = 0;
        }
        // Conflux heroes hack, Conflux hero -> castle hero
        else if (H3M_OBJECT_HERO == oa_type) {
            if (0 == stricmp(entry_out->header.def, "ah16_e.def")) {
                _snprintf(entry_out->header.def, entry_out->header.def_size,
                    "%s", "ah00_e.def");
                entry_out->body.object_number = 0;
            } else if (0 == stricmp(entry_out->header.def, "ah17_e.def")) {
                _snprintf(entry_out->header.def, entry_out->header.def_size,
                    "%s", "ah01_e.def");
                entry_out->body.object_number = 1;
            }
        }

        entry_conv = calloc(1, sizeof(*entry_conv));
        entry_conv->oa_index_in = i;
        entry_conv->oa_index_out = count;
        entry_conv->body_size_delta = body_size_delta;
        entry_conv->convert_binary_compatible = convert_binary_compatible;
        HASH_ADD_INT(conv->oa_hash, oa_index_in, entry_conv);

        ++count;
    }

    ctx_out->h3m.oa.count = count;

    return 0;
}

static int _inline_conv_artifacts(uint32_t fm_src,
    union H3M_COMMON_ARTIFACTS *artifacts)
{
    size_t extra_size = 0;
    union H3M_COMMON_BACKPACK *backpack_src =
        (H3M_FORMAT_AB ==
        fm_src) ? (union H3M_COMMON_BACKPACK *)&artifacts->ab.
        backpack : (union H3M_COMMON_BACKPACK *)&artifacts->sod.backpack;
    size_t count = backpack_src->any.count;
    size_t src_backpack_size =
        (count * sizeof(backpack_src->absod.artifacts[0]))
        + ((H3M_FORMAT_AB ==
            fm_src) ? sizeof(artifacts->ab) : sizeof(artifacts->sod));
    size_t extra_backpack_size = src_backpack_size - sizeof(artifacts->roe);

    artifacts->roe.backpack.count = backpack_src->any.count;
    // Keep in mind this simple approach cannot be taken in the other direction
    for (unsigned int i = 0; i < count; ++i) {
        artifacts->roe.backpack.artifacts[i] =
            (uint8_t) backpack_src->absod.artifacts[i];
    }

    return 0;
}

static int _inline_conv_army(union H3M_COMMON_ARMY *army, int creature_count)
{
    size_t extra_size = 0;
    unsigned int idx = 0;

    // TODO: check for any incompatible creature types and replace them

    // Keep in mind this simple approach cannot be taken in the other direction
    for (int i = 0; i < creature_count; ++i) {
        idx = (H3M_COMMON_ARTIFACT_TYPE_ROE) army->absod.slots[i].type;
        if (idx <
            sizeof(creature_type_conv_table_roe) /
            sizeof(creature_type_conv_table_roe[0])) {
            army->roe.slots[i].type =
                (uint8_t) creature_type_conv_table_roe[idx];
            army->roe.slots[i].quantity = army->absod.slots[i].quantity;
            army->roe.slots[i].quantity *= creature_multiplier_table_roe[idx];
        } else {
            army->roe.slots[i].type = 0xFF;
            army->roe.slots[i].quantity = 0;
        }
    }

    extra_size = (creature_count * sizeof(army->absod.slots[0]))
        - (creature_count * sizeof(army->roe.slots[0]));
    memset((uint8_t *)army + (sizeof(army->roe.slots[0]) * creature_count), 0,
        extra_size);

    return 0;
}

static int _inline_conv_event(uint32_t fm_src,
    struct H3M_OD_BODY_DYNAMIC_EVENT *body)
{
    if (NULL != body->guardians.creatures) {
        _inline_conv_army(body->guardians.creatures, MAX_CREATURES);
    }
#if 1
    if (NULL != body->contents.creatures) {
        _inline_conv_army(body->contents.creatures,
            body->contents.creatures_count);
    }
#endif

    return 0;
}

static uint8_t _hero_type_to_roe(uint8_t expansion_type)
{
    // This function is a hack and wont work well if result hero already exists on map.
    // TODO logic for detecting whether desired conversion target already exists on map.

    // Conflux heroes
    if (expansion_type >= 0x80 && expansion_type < 0x90) {
        return expansion_type - 0x80;
    }
    // Campaign/extra heroes
    switch (expansion_type) {
    case 0x9B:                 // Xeron->Calh
        return 0x35;
    case 0x98:                 // Roland->Orrin
    case 0x90:                 // Sir Mullich->Orrin
        return 0x0;
    case 0x91:                 // Adrienne->Verdish
        return 0x7b;
    case 0x92:                 // Catherine->Tyris
        return 0x07;
    case 0x93:                 // Dracon->Astral
        return 0x28;
    case 0x94:                 // Gelu->Kyrre
        return 0x17;
    case 0x9A:                 // Boragos->Tyraxor
    case 0x95:                 // Kilgor->Tyraxor
        return 0x67;
    case 0x96:                 // Undead Lord Haart->Vokial
        return 0x41;
    case 0x97:                 // Mutare->Shakti
    case 0x99:                 // Mutare Drake->Shakti
        return 0x57;
    default:
        break;
    }

    // TODO: Proper conversion for WoG heroes here

#ifdef _WIN32
    OutputDebugStringA("No conversion for this hero value, setting 0x00");
#endif

    return 0x00;
}

static int _inline_conv_hero(uint32_t fm_src,
    struct H3M_OD_BODY_DYNAMIC_HERO *body, struct H3M_OD_ENTRY *entry_out,
    struct CONV_CTX *conv)
{
    int ret = 0;
    char log_msg[256] = { 0 };

    // 0x80 is where conflux + AB campaign heroes begin, except 0xFF which is random
    if (0 != body->has_face && (body->face >= 0x80 && 0xFF != body->face)) {
        body->face = _hero_type_to_roe(body->face);
        _snprintf(log_msg, sizeof(log_msg) - 1,
            "[!] Lost AB/SoD Hero face for hero @%d,%d,%d\n",
            entry_out->header.x, entry_out->header.y, entry_out->header.z);
        _log_msg(conv, LOG_WARNING, log_msg);
        ret = 2;
    }
    // TODO need to prevent hero conflict (e.g could add all taken heroes
    // to a hash map during read, then check if the desired conversion is 
    // possible here)

    if (body->type >= 0x80 && 0xFF != body->type) {
        body->type = _hero_type_to_roe(body->type);
        _snprintf(log_msg, sizeof(log_msg) - 1,
            "[!] Lost AB/SoD Hero type for hero @%d,%d,%d\n",
            entry_out->header.x, entry_out->header.y, entry_out->header.z);
        _log_msg(conv, LOG_WARNING, log_msg);
        ret = 2;
    }

    if (NULL != body->artifacts) {
        _inline_conv_artifacts(fm_src, body->artifacts);
    }
    if (NULL != body->creatures) {
        _inline_conv_army(body->creatures, MAX_CREATURES);
    }

    if (0 != body->has_secondary_skills && (NULL == body->secondary_skills)) {
        body->has_secondary_skills = 0;
    }

    return ret;
}

static int _inline_conv_pandoras_box(uint32_t fm_src,
    struct H3M_OD_BODY_DYNAMIC_PANDORAS_BOX *body)
{
    if (NULL != body->guardians.creatures) {
        _inline_conv_army(body->guardians.creatures, MAX_CREATURES);
    }
    if (NULL != body->contents.creatures) {
        _inline_conv_army(body->contents.creatures,
            body->contents.creatures_count);
    }

    return 0;
}

static int _inline_conv_town(uint32_t fm_src,
    struct H3M_OD_BODY_DYNAMIC_TOWN *body)
{
    if (NULL != body->creatures) {
        _inline_conv_army(body->creatures, MAX_CREATURES);
    }

    return 0;
}

static int _reset_meta_push_od(uint32_t fm_out, uint8_t *body,
    struct META_OD_ENTRY *meta)
{
    free_dyn_pointers(meta->dyn_pointers, 0);
    meta->dyn_pointers = NULL;
    meta_push_od(fm_out, body, meta);
    return 0;
}

static int _od_body_conv(struct H3MLIB_CTX *ctx_in,
    struct H3MLIB_CTX *ctx_out,
    struct H3M_OD_ENTRY *entry_in,
    struct H3M_OD_ENTRY *entry_out,
    struct META_OD_ENTRY *meta_in,
    struct META_OD_ENTRY *meta_out, struct CONV_CTX *conv)
{
    // Copy body, taking ownership of pointers
    entry_out->body = malloc(meta_in->body_size);
    memcpy(entry_out->body, entry_in->body, meta_in->body_size);
    memcpy(meta_out, meta_in, sizeof((*meta_out)));
    meta_in->dyn_pointers = NULL;

    meta_out->has_absod_id = 0;

    switch (meta_in->oa_type) {
    case H3M_OBJECT_GARRISON:
        _inline_conv_army((union H3M_COMMON_ARMY *)&((union
                    H3M_OD_BODY_STATIC_GARRISON *)entry_out->body)->any.
            creatures, MAX_CREATURES);
        ((struct H3M_OD_BODY_STATIC_GARRISON_ABSOD *)entry_out->body)->
            removable_units = 0;
        meta_out->body_size -= sizeof(struct H3M_OD_BODY_STATIC_GARRISON_ABSOD)
            - sizeof(struct H3M_OD_BODY_STATIC_GARRISON_ROE);
        return 0;
#if 1
    case H3M_OBJECT_EVENT:
        _inline_conv_event(ctx_in->h3m.format,
            (struct H3M_OD_BODY_DYNAMIC_EVENT *)entry_out->body);
        return _reset_meta_push_od(ctx_out->h3m.format, entry_out->body,
            meta_out);
    case H3M_OBJECT_PANDORAS_BOX:
        _inline_conv_pandoras_box(ctx_in->h3m.format,
            (struct H3M_OD_BODY_DYNAMIC_PANDORAS_BOX *)entry_out->body);
        return _reset_meta_push_od(ctx_out->h3m.format, entry_out->body,
            meta_out);
#endif
#if 1
    case H3M_OBJECT_TOWN:
    case H3M_OBJECT_TOWN_ABSOD:
        _inline_conv_town(ctx_in->h3m.format,
            (struct H3M_OD_BODY_DYNAMIC_TOWN *)entry_out->body);
        return _reset_meta_push_od(ctx_out->h3m.format, entry_out->body,
            meta_out);
#endif
#if 1
    case H3M_OBJECT_HERO:
    case H3M_OBJECT_PRISON:
    case H3M_OBJECT_RANDOM_HERO:
        _inline_conv_hero(ctx_in->h3m.format,
            (struct H3M_OD_BODY_DYNAMIC_HERO *)entry_out->body, entry_out,
            conv);
        return _reset_meta_push_od(ctx_out->h3m.format, entry_out->body,
            meta_out);
#endif
    case H3M_OBJECT_MONSTER:
        if (((struct H3M_OD_BODY_DYNAMIC_MONSTER *)entry_out->body)->
            has_mesg_and_treasure) {
            --meta_out->body_size;      // Treasure artifact: uint16_t->uint8_t
        }
        return 0;
#if 1
    case H3M_OBJECT_ARTIFACT:
    case H3M_OBJECT_RESOURCE:
    case H3M_OBJECT_SPELL_SCROLL:
        // this type cast is fine for resource too
        if (NULL != ((struct H3M_OD_BODY_DYNAMIC_ARTIFACT *)
            entry_out->body)->guardians.creatures) {
            free_dyn_pointers(meta_out->dyn_pointers, 0);
            meta_out->dyn_pointers = NULL;
            meta_push_od(H3M_FORMAT_ROE, (uint8_t *)entry_out->body, meta_out);
            _inline_conv_army(((struct H3M_OD_BODY_DYNAMIC_ARTIFACT *)
                    entry_out->body)->guardians.creatures, MAX_CREATURES);
        }
        return 0;
#endif
    case H3M_OBJECT_OCEAN_BOTTLE:
    case H3M_OBJECT_SIGN:
        return 0;
    default: // fail
        break;
    }

    // Cleanup the pointers we alloc'd and took ownership of
    if (NULL != meta_out->dyn_pointers) {
        free_dyn_pointers(meta_out->dyn_pointers, 1);
        meta_out->dyn_pointers = NULL;
    }
    free(entry_out->body);
    entry_out->body = NULL;
    memset(meta_out, 0, sizeof((*meta_out)));

    return 1;
}

static int _convert_od_roe(struct H3MLIB_CTX *ctx_in,
    struct H3MLIB_CTX *ctx_out, struct CONV_CTX *conv)
{
    size_t max_count = ctx_in->h3m.od.count;
    size_t count = 0;
    struct H3M_OD_ENTRY *entry_in = NULL;
    struct H3M_OD_ENTRY *entry_out = NULL;
    struct META_OD_ENTRY *meta_in = NULL;
    struct META_OD_ENTRY *meta_out = NULL;
    struct H3M_OA_ENTRY *oa_in = NULL;
    struct OA_HASH *entry_conv = NULL;
    unsigned int i = 0;
    int ret = 0;
    char log_msg[256] = { 0 };
    uint8_t *default_body = NULL;
    uint64_t *passability;

    if (NULL != ctx_out->h3m.od.entries) {
        free(ctx_out->h3m.od.entries);
    }
    if (NULL != ctx_out->meta.od_entries) {
        free(ctx_out->meta.od_entries);
    }
    ctx_out->h3m.od.entries = calloc(max_count, sizeof(*(entry_out)));
    ctx_out->meta.od_entries = calloc(max_count, sizeof(*(meta_out)));

    for (i = 0; i < max_count; ++i) {
        entry_in = &ctx_in->h3m.od.entries[i];
        meta_in = &ctx_in->meta.od_entries[i];
        entry_out = &ctx_out->h3m.od.entries[count];
        meta_out = &ctx_out->meta.od_entries[count];

        HASH_FIND_INT(conv->oa_hash, &entry_in->header.oa_index, entry_conv);

        if (NULL == entry_conv) {
            if (H3M_OBJECT_GENERIC_IMPASSABLE_TERRAIN_ABSOD == meta_in->oa_type) {
                oa_in = &ctx_in->h3m.oa.entries[entry_in->header.oa_index];
                passability = (uint64_t *)oa_in->body.passable;

                h3m_impassable_mark(ctx_out, entry_in->header.x,
                    entry_in->header.y, entry_in->header.z,
                    *passability, (uint8_t *)conv->impassable,
                    ctx_out->h3m.bi.any.map_size);

                snprintf(log_msg, sizeof(log_msg) - 1,
                    "[*] REPLACED terrain at [%d,%d,%d] with RoE-compatible terrain\n",
                    entry_in->header.x, entry_in->header.y, entry_in->header.z);
                _log_msg(conv, LOG_INFO, log_msg);
            } else {
                snprintf(log_msg, sizeof(log_msg) - 1,
                    "[!!!] LOST object %s at [%d,%d,%d]\n",
                    H3M_OBJECT_CATEGORIES[meta_in->oa_type], entry_in->header.x,
                    entry_in->header.y, entry_in->header.z);
                // Loss of SoD passable terrain (fiery clouds etc) is comparatively not that bad, so just log as warning
                _log_msg(conv,
                    (H3M_OBJECT_GENERIC_PASSABLE_TERRAIN_SOD !=
                        meta_in->oa_type) ? LOG_CRITICAL : LOG_WARNING,
                    log_msg);
            }

            continue;
        }

        memcpy(&entry_out->header, &entry_in->header, sizeof(entry_in->header));
        entry_out->header.oa_index = entry_conv->oa_index_out;

        // If object is body-less conversion is done, move on to next
        if (NULL == entry_in->body) {
            ++count;
            continue;
        }

        if (0 == meta_in->binary_compatible
            || 0 != entry_conv->convert_binary_compatible) {
            // Attempt to convert customization to RoE
            if (0 != (ret = _od_body_conv(ctx_in, ctx_out, entry_in, entry_out,
                        meta_in, meta_out, conv))) {
                // Object conversion failed - fall back to defaults
                if (0 != (get_default_od_body(meta_in->oa_type,
                            &entry_out->body,
                            &meta_out->binary_compatible,
                            &meta_out->body_size))) {
                    // Getting default version of object failed - object lost
                    snprintf(log_msg, sizeof(log_msg) - 1,
                        "[!!!] LOST object %s at [%d,%d,%d]\n",
                        H3M_OBJECT_CATEGORIES[meta_in->oa_type],
                        entry_in->header.x, entry_in->header.y,
                        entry_in->header.z);
                    // Loss of SoD passable terrain (fiery clouds etc) is comparatively not that bad, so just log as warning
                    _log_msg(conv, LOG_CRITICAL, log_msg);

                    continue;
                } else {
                    // Object added with defaults
                    snprintf(log_msg, sizeof(log_msg) - 1,
                        "[!] LOST customization for %s at [%d,%d,%d]\n",
                        H3M_OBJECT_CATEGORIES[meta_in->oa_type],
                        entry_out->header.x,
                        entry_out->header.y, entry_out->header.z);
                    _log_msg(conv, LOG_WARNING, log_msg);
                }
            }
        } else { // Binary compatible
            meta_out->binary_compatible = 1;
            meta_out->body_size = meta_in->body_size;
            meta_out->body_size += entry_conv->body_size_delta;

            if (0 != meta_out->body_size) {
                entry_out->body = malloc(meta_out->body_size);
                memcpy(entry_out->body, entry_in->body, meta_out->body_size);
            }
        }

        ++count;
    }

    ctx_out->h3m.od.count = count;
    ctx_out->meta.od_entries_count = count;

    h3m_impassable_fill(ctx_out, (uint8_t *)conv->impassable,
        ctx_out->h3m.bi.any.map_size);

    return 0;
}

static int _convert_events_roe(struct H3MLIB_CTX *ctx_in,
    struct H3MLIB_CTX *ctx_out, struct CONV_CTX *conv)
{
    struct H3M_EVENT_ENTRY *entry_in = 0;
    struct H3M_EVENT_ENTRY *entry_out = 0;
    size_t n = 0;
    size_t count = 0;

    if (H3M_FORMAT_AB == ctx_in->h3m.format) {
        // AB events are compatible with RoE - simply copy over and take ownership
        // of event pointers
        memcpy(&ctx_out->h3m.event, &ctx_in->h3m.event,
            sizeof(ctx_out->h3m.event));
        memset(&ctx_in->h3m.event, 0, sizeof(ctx_in->h3m.event));
        return 0;
    }

    count = ctx_in->h3m.event.count;
    if (0 != count) {
        // SoD events are not compatible (one extra uint8_t member: applies_to_human), 
        // so iterate and convert individually
        ctx_out->h3m.event.count = count;
        ctx_out->h3m.event.entries =
            calloc(count, sizeof(*(ctx_out->h3m.event.entries)));
        for (unsigned int i = 0; i < ctx_in->h3m.event.count; ++i) {
            entry_in = &ctx_in->h3m.event.entries[i];
            entry_out = &ctx_out->h3m.event.entries[i];
            // Note that pointers are copied here for the header, ownership taken below
            n = sizeof(entry_out->header) +
                sizeof(entry_out->body.roeab.resources)
                + sizeof(entry_out->body.roeab.applies_to_players);
            memcpy(entry_out, entry_in, n);
            // 1 byte applies_to_human is skipped here
            n = sizeof(entry_out->body.roeab.first_occurence)
                + sizeof(entry_out->body.roeab.subsequent_occurences)
                + sizeof(entry_out->body.roeab.unknown2);
            memcpy(&entry_out->body.roeab.applies_to_computer,
                &entry_in->body.sod.applies_to_computer, n);

            // Take ownership of pointers
            memset(entry_in, 0, sizeof((*entry_out)));
        }
    }

    return 0;
}

static int _inline_conv_win_cond(uint8_t win_cond_type,
    union H3M_AI_WIN_COND *win_cond, size_t *win_cond_size)
{
    switch (win_cond_type) {
    case C_ACCUMULATE_CREATURES:
        win_cond->c_accumulate_creatures.roe.amount =
            win_cond->c_accumulate_creatures.absod.amount;
        // fall through
    case C_ACQUIRE_ARTIFACT:
        --(*win_cond_size);     // Creature / artifact type uint16_t -> uint8_t
        break;
    default:
        break;
    }

    return 0;
}

static int _convert_players(struct H3MLIB_CTX *ctx_in,
    struct H3MLIB_CTX *ctx_out)
{
    uint32_t fm_src = ctx_in->h3m.format;
    size_t n = 0;
    union H3M_PLAYER *player = NULL;
    union H3M_PLAYER_EXT_ROE *player_ext_out = NULL;
    union H3M_PLAYER_EXT_ABSOD *player_ext_in = NULL;
    size_t name_size = 0;
    size_t ext_size = 0;

    // Free existing players in output
    if (NULL != ctx_out->h3m.players) {
        free_players(ctx_out->h3m.players);
    }
    // Copy structures and meta data, take ownership of players
    ctx_out->h3m.players = ctx_in->h3m.players;
    ctx_in->h3m.players = NULL;
    memcpy(&ctx_out->meta.player_sizes, ctx_in->meta.player_sizes,
        sizeof(ctx_out->meta.player_sizes));
    memcpy(ctx_out->meta.player_ext_types, ctx_in->meta.player_ext_types,
        sizeof(ctx_out->meta.player_ext_types));

    // Inline convert structures and adjust metadata
    for (int i = 0; i < H3M_MAX_PLAYERS; ++i) {
        player = ctx_out->h3m.players[i];
        player_ext_out = &player->roe.u;

        if (H3M_FORMAT_AB == fm_src) {
            // AB - town_types is at same offset
            player->roe.unknown1 = player->ab.unknown1;
            player->roe.has_main_town = player->ab.has_main_town;
            player_ext_in = &player->ab.u;
        } else {
            uint8_t allowed = player->sod.allowed_alignments;
            player->roe.town_types = player->sod.town_types;

            player->roe.unknown1 = player->sod.unknown1;
            player->roe.has_main_town = player->sod.has_main_town;
            player_ext_in = &player->sod.u;
        }

        switch (ctx_out->meta.player_ext_types[i]) {
        case 0:
            ext_size = sizeof(player->roe.u.e0);
            player_ext_out->e0.starting_hero_is_random =
                player_ext_in->e0.starting_hero_is_random;
            player_ext_out->e0.starting_hero_type =
                player_ext_in->e0.starting_hero_type;
            break;
        case 1:
            ext_size = sizeof(player_ext_out->e1);
            memmove(&player_ext_out->e1.starting_town_xpos,
                &player_ext_in->e1.starting_town_xpos, ext_size);
            break;
        case 2:
            ext_size = sizeof(player_ext_out->e2);
            memmove(&player_ext_out->e2, &player_ext_in->e2, ext_size);

#if 1
            // If hero is an expansion hero, simply remove it from here
            if (player_ext_out->e2.starting_hero_type >= 0x80
                || (player_ext_out->e2.starting_hero_face >= 0x80
                    && 0xFF != player_ext_out->e2.starting_hero_face)) {
                // e2 -> e0
                player_ext_out->e0.starting_hero_is_random = 0;
                player_ext_out->e0.starting_hero_type = 0xFF;
                ctx_out->meta.player_ext_types[i] = 0;
                ext_size = sizeof(player->roe.u.e0);
                break;
            }
#endif
            name_size = player_ext_out->e2.starting_hero_name_size;
            memmove(&player_ext_out->e2.starting_hero_name,
                &player_ext_in->e2.starting_hero_name, name_size);

            ext_size += name_size;
            break;
        case 3:
            ext_size = sizeof(player_ext_out->e3);
            memmove(&player_ext_out->e3.starting_town_xpos,
                &player_ext_in->e3.starting_town_xpos, ext_size);
#if 1
            // If hero is an expansion hero, simply remove it from here
            if (player_ext_out->e3.starting_hero_type >= 0x80
                || player_ext_out->e3.starting_hero_face >= 0x80) {
                // e3 -> e1
                player_ext_out->e1.starting_hero_is_random = 0;
                player_ext_out->e1.starting_hero_type = 0xFF;
                ctx_out->meta.player_ext_types[i] = 1;
                ext_size = sizeof(player->roe.u.e1);
                break;
            }
#endif
            name_size = player_ext_out->e3.starting_hero_name_size;
            memmove(&player_ext_out->e3.starting_hero_name,
                &player_ext_in->e3.starting_hero_name, name_size);

            ext_size += name_size;
            break;
        default:
            return 1;
        }
        ctx_out->meta.player_sizes[i] =
            sizeof(player->roe) - sizeof(player->roe.u)
            + ext_size;
    }

    return 0;
}

static int _convert_ai(struct H3MLIB_CTX *ctx_in, struct H3MLIB_CTX *ctx_out)
{
    struct H3M_AI_RUMOR **rumors_in = NULL;

    // Convert AI, take ownership of rumors
    memcpy(&ctx_out->h3m.ai, &ctx_in->h3m.ai,
        (sizeof(ctx_out->h3m.ai.any.win_cond_type)
            + sizeof(ctx_out->h3m.ai.any.win_cond),
            +sizeof(ctx_out->h3m.ai.any.lose_cond_type),
            +sizeof(ctx_out->h3m.ai.any.lose_cond),
            +sizeof(ctx_out->h3m.ai.any.teams_count),
            +sizeof(ctx_out->h3m.ai.any.teams),
            +sizeof(ctx_out->h3m.ai.any.available_heroes)));

    memcpy(&ctx_out->h3m.ai.any.teams, &ctx_in->h3m.ai.any.teams,
        sizeof(ctx_out->h3m.ai.any.teams));
    ctx_out->meta.ai_win_cond_size = ctx_in->meta.ai_win_cond_size;
    ctx_out->meta.ai_lose_cond_size = ctx_in->meta.ai_lose_cond_size;
    ctx_out->meta.ai_teams_size = ctx_in->meta.ai_teams_size;
    ctx_out->meta.ai_lose_cond_size = ctx_in->meta.ai_lose_cond_size;

    _inline_conv_win_cond(ctx_out->h3m.ai.roe.win_cond_type,
        &ctx_out->h3m.ai.roe.win_cond,
        (size_t *)& ctx_out->meta.ai_win_cond_size);

    ctx_out->h3m.ai.roe.rumors_count = ((H3M_FORMAT_AB == ctx_in->h3m.format) ?
        ctx_in->h3m.ai.ab.rumors_count : ctx_in->h3m.ai.sod.rumors_count);
    rumors_in = ((H3M_FORMAT_AB == ctx_in->h3m.format) ?
        &ctx_in->h3m.ai.ab.rumors : &ctx_in->h3m.ai.sod.rumors);
    ctx_out->h3m.ai.roe.rumors = *rumors_in;
    *rumors_in = NULL;

    return 0;
}

const char *get_prefix(enum H3M_FORMAT fm)
{
    switch (fm) {
    case H3M_FORMAT_SOD:
        return PREFIX_SOD;
    case H3M_FORMAT_AB:
        return PREFIX_AB;
    case H3M_FORMAT_WOG:
        return PREFIX_WOG;
    default:
        break;
    }

    return PREFIX_UNKNOWN;
}

static int _convert_to_roe(struct H3MLIB_CTX *ctx_in,
    struct H3MLIB_CTX **ctx_out)
{
    uint32_t fm_src = ctx_in->h3m.format;
    struct CONV_CTX conv = { 0 };
    struct H3MLIB_CTX *ctx_tmp = NULL;
    size_t n = 0;
    size_t map_size = ctx_in->h3m.bi.any.map_size;
    int has_two_levels = ctx_in->h3m.bi.any.has_two_levels;
    char *new_str = NULL;
    const char *prefix = get_prefix(fm_src);

    h3m_init_min(&ctx_tmp, H3M_FORMAT_ROE, 36);

    // Convert BI
    memcpy(&ctx_tmp->h3m.bi, &ctx_in->h3m.bi, sizeof(ctx_tmp->h3m.bi.roe));

    // Fix-up name and desc
    ctx_tmp->h3m.bi.any.name_size += strlen(prefix);
    ctx_tmp->h3m.bi.any.name = calloc(1, ctx_tmp->h3m.bi.any.name_size + 1);
#ifdef _WIN32
    _snprintf(ctx_tmp->h3m.bi.any.name, ctx_tmp->h3m.bi.any.name_size, "%s%s",
        prefix, ctx_in->h3m.bi.any.name);
#else
    snprintf((char *)ctx_tmp->h3m.bi.any.name, ctx_tmp->h3m.bi.any.name_size,
        "%s %s", (H3M_FORMAT_AB == fm_src) ? PREFIX_AB : PREFIX_SOD,
        ctx_in->h3m.bi.any.name);
#endif
    ctx_tmp->h3m.bi.any.desc_size += sizeof(SUFFIX_DESC);
    ctx_tmp->h3m.bi.any.desc = calloc(1, ctx_tmp->h3m.bi.any.desc_size + 1);
#ifdef _WIN32
    _snprintf((char *)ctx_tmp->h3m.bi.any.desc, ctx_tmp->h3m.bi.any.desc_size,
        "%s %s", ctx_in->h3m.bi.any.desc ? ctx_in->h3m.bi.any.desc : "",
        SUFFIX_DESC);
#else
    snprintf((char *)ctx_tmp->h3m.bi.any.desc, ctx_tmp->h3m.bi.any.desc_size,
        "%s %s", ctx_in->h3m.bi.any.desc, SUFFIX_DESC);
#endif

    // Heroes III HD Edition does not support maps with longer desc than 300
    if (ctx_tmp->h3m.bi.any.desc_size > 300) {
        ctx_tmp->h3m.bi.any.desc_size = 300;
        ctx_tmp->h3m.bi.any.desc[300] = 0;
    }

    _conv_init(&conv, ctx_tmp->h3m.bi.any.name);

    _convert_players(ctx_in, ctx_tmp);
    _convert_ai(ctx_in, ctx_tmp);

    // Take ownership of tiles
    free(ctx_tmp->h3m.tiles);
    ctx_tmp->h3m.tiles = ctx_in->h3m.tiles;
    ctx_in->h3m.tiles = NULL;

    _convert_oa_roe(ctx_in, ctx_tmp, &conv);
    _convert_od_roe(ctx_in, ctx_tmp, &conv);
    _convert_events_roe(ctx_in, ctx_tmp, &conv);

    _conv_exit(&conv);

    *ctx_out = ctx_tmp;
    return 0;
}

struct CB_DATA_WRAPPER {
    uint32_t fm_src;
    h3m_parse_cb_t user_cb;
    void *user_cb_data;
};

static int _h3m_read_cb(uint32_t offset, const char *member, void *p, size_t n,
    void *cb_data)
{
    struct CB_DATA_WRAPPER *wrap = (struct CB_DATA_WRAPPER *)cb_data;

    if (0 == offset) {
        // Preserve format here, so that it is known even if h3m parse fails and is cleaned up
        wrap->fm_src = *(uint32_t *)p;

        if (H3M_FORMAT_ROE == wrap->fm_src) {
            return 1;
        }
    }

    if (NULL != wrap->user_cb) {
        return wrap->user_cb(offset, member, p, n, wrap->user_cb_data);
    }

    return 0;
}

int h3m_read_convert(h3mlib_ctx_t *ctx,
    const char *filename,
    enum H3M_FORMAT target_format,
    enum H3M_FORMAT *source_format,
    h3m_parse_cb_t cb_parse,
    h3m_error_cb_t cb_error, h3m_custom_def_cb_t cb_def, void *cb_data)
{
    h3mlib_ctx_t ctx_in = NULL;
    int ret = 0;
    struct CB_DATA_WRAPPER wrap = { 0 };
    wrap.user_cb = cb_parse;
    wrap.user_cb_data = cb_data;

    ret = h3m_read_with_cbs(&ctx_in, filename, _h3m_read_cb, cb_error, 
        cb_def, &wrap);

    if (NULL != source_format) {
        *source_format = wrap.fm_src;
    }

    if (NULL == ctx_in) {
        return -1;
    }

    switch (target_format) {
    case H3M_FORMAT_ROE:
        ret = _convert_to_roe((struct H3MLIB_CTX *)ctx_in,
            (struct H3MLIB_CTX **)ctx);
    default:
        break;
    }

    h3m_exit(&ctx_in);

    return ret;
}

int h3m_read_convert_u(h3mlib_ctx_t *ctx,
    const wchar_t *filename,
    enum H3M_FORMAT target_format,
    enum H3M_FORMAT *source_format,
    h3m_parse_cb_t cb_parse,
    h3m_error_cb_t cb_error, h3m_custom_def_cb_t cb_def, void *cb_data)
{
    h3mlib_ctx_t ctx_in = NULL;
    int ret = 0;
    struct CB_DATA_WRAPPER wrap = { 0 };
    wrap.user_cb = cb_parse;
    wrap.user_cb_data = cb_data;

    ret = h3m_read_with_cbs_u(&ctx_in, filename, _h3m_read_cb, cb_error, 
        cb_def, &wrap);

    if (NULL != source_format) {
        *source_format = wrap.fm_src;
    }

    if (NULL == ctx_in) {
        return -1;
    }

    switch (target_format) {
    case H3M_FORMAT_ROE:
        ret = _convert_to_roe((struct H3MLIB_CTX *)ctx_in,
            (struct H3MLIB_CTX **)ctx);
    default:
        break;
    }

    h3m_exit(&ctx_in);

    return ret;
}