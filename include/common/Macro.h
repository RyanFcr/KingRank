#ifndef MACROS_H_
#define MACROS_H_

/// \brief Text Style
#define RESET_ 0
#define BOLD_ 1
#define FAINT_ 2
#define ITALIC_ 3
#define UNDERLINE_ 4
#define SLOWBLINK_ 5
#define RAPIDBLINK_ 6
#define BLACK_ 30
#define RED_ 31
#define GREEN_ 32
#define YELLOW_ 33
#define BLUE_ 34
#define MAGENTA_ 35
#define CYAN_ 36
#define WHITE_ 37
#define BLACK_BACK_ 40
#define RED_BACK_ 41
#define GREEN_BACK_ 42
#define YELLOW_BACK_ 43
#define BLUE_BACK_ 44
#define MAGENTA_BACK_ 45
#define CYAN_BACK_ 46
#define WHITE_BACK_ 47

/// \brief Simple Utils
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

// Json相关
#define DOM_OBJECT_MEMBER_TO_VAR_STRING(OBJECT, MEMBER, VAR) \
    do {                                                     \
        if (!OBJECT.HasMember(MEMBER))                       \
            throw HAS_PARSE_ERROR;                           \
        if (!OBJECT[MEMBER].IsString())                      \
            throw HAS_PARSE_ERROR;                           \
        VAR = OBJECT[MEMBER].GetString();                    \
    } while (0);

#define DOM_OBJECT_MEMBER_TO_VAR_INT(OBJECT, MEMBER, VAR) \
    do {                                                  \
        if (!OBJECT.HasMember(MEMBER))                    \
            throw HAS_PARSE_ERROR;                        \
        if (!OBJECT[MEMBER].IsInt())                      \
            throw HAS_PARSE_ERROR;                        \
        VAR = OBJECT[MEMBER].GetInt();                    \
    } while (0);

#define PARSE_DOM_OBJECT(DOM_OBJECT, JSON_STRING)          \
    do {                                                   \
        if (DOM_OBJECT.Parse(JSON_STRING).HasParseError()) \
            throw HAS_PARSE_ERROR;                         \
        if (!DOM_OBJECT.IsObject())                        \
            throw HAS_PARSE_ERROR;                         \
    } while (0);

#define ASSERT_DOM_OBJECT_HAS_MEMBER(OBJECT, MEMBER) \
    do {                                             \
        if (!OBJECT.HasMember(MEMBER))               \
            throw HAS_PARSE_ERROR;                   \
    } while (0);

#define ASSERT_DOM_OBJECT_IS_ARRAY(OBJECT) \
    do {                                   \
        if (!OBJECT.IsArray())             \
            throw HAS_PARSE_ERROR;         \
    } while (0);

#define ASSERT_DOM_OBJECT_IS_OBJECT(OBJECT) \
    do {                                    \
        if (!OBJECT.IsObject())             \
            throw HAS_PARSE_ERROR;          \
    } while (0);

#define WRITE_DOM_OBJECT_MEMBER_INT(OBJECT, MEMBER)               \
    do {                                                          \
        writer.String(MEMBER);                                    \
        if (!OBJECT.HasMember(MEMBER) || !OBJECT[MEMBER].IsInt()) \
            throw HAS_PARSE_ERROR;                                \
        writer.Int(OBJECT[MEMBER].GetInt());                      \
    } while (0);

#define WRITE_DOM_OBJECT_MEMBER_STRING(OBJECT, MEMBER)               \
    do {                                                             \
        writer.String(MEMBER);                                       \
        if (!OBJECT.HasMember(MEMBER) || !OBJECT[MEMBER].IsString()) \
            throw HAS_PARSE_ERROR;                                   \
        writer.String(OBJECT[MEMBER].GetString());                   \
    } while (0);

#define ADD_MEMBER_STRING(OBJECT, MEMBER, VALUE)                                                                      \
    do {                                                                                                              \
        OBJECT.AddMember(MEMBER, Value().SetString(VALUE.c_str(), static_cast<SizeType>(VALUE.length())), allocator); \
    } while (0);

#define ADD_MEMBER_INT(OBJECT, MEMBER, VALUE)                       \
    do {                                                            \
        OBJECT.AddMember(MEMBER, Value().SetInt(VALUE), allocator); \
    } while (0);

#define SERIALIZE_STRING(MEMBER, VALUE)                                      \
    do {                                                                     \
        writer.String(MEMBER);                                               \
        writer.String(VALUE.c_str(), static_cast<SizeType>(VALUE.length())); \
    } while (0);

#define SERIALIZE_INT(MEMBER, VALUE) \
    do {                             \
        writer.String(MEMBER);       \
        writer.Int(VALUE);           \
    } while (0);
#endif  // MACROS_H_