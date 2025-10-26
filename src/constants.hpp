#pragma once

#include <cstdint>

#define FRICTION 0.85
#define ACCEL 0.6
#define WORLD_X 600
#define WORLD_Y 600
#define MAX_HEALTH 100
#define HEALTH_DRAIN 0.02
#define BALL_RADIUS 15
#define BULLET_MAXAGE 240
#define BULLET_SPEED 7
#define BULLET_RADIUS 6
#define BULLET_DAMAGE 15
#define MAX_FEAR 900
#define FIRING_COOLDOWN 60
#define BLAST_MAXAGE 10
#define BLAST_GROWTH 4
#define PADDING 100
#define PADDED_VEC2(x, y)        \
    Vector2 {                    \
        PADDING + x, PADDING + y \
    }
#define PADDED_REC(x, y, width, height)         \
    Rectangle {                                 \
        PADDING + x, PADDING + y, width, height \
    }
#define PADDING_V        \
    Vector2 {            \
        PADDING, PADDING \
    }

typedef std::int8_t i8;
typedef std::uint8_t u8;
typedef std::int16_t i16;
typedef std::uint16_t u16;
typedef std::int32_t i32;
typedef std::uint32_t u32;
typedef std::int64_t i64;
typedef std::uint64_t u64;
typedef float f32;
typedef double f64;
typedef std::ptrdiff_t isize;
typedef std::size_t usize;

static_assert(sizeof(f32) == 4);
static_assert(sizeof(f64) == 8);
static_assert(sizeof(isize) == 8);
static_assert(sizeof(usize) == 8);
