#ifndef DATATYPES_H
#define DATATYPES_H 1
/****************************** For Boolean Types *****************************/
typedef unsigned char bool; /** For boolean types **/
#define true  (!0)
#define false  (0)
/***************************** !For Boolean Types *****************************/

typedef unsigned char uint8_t;

/****** Forward declare a couple of things until we have implemented them *****/
typedef struct _GameList GameList;
typedef struct _Team     Team;
typedef struct _Game     Game;
/***** !Forward declare a couple of things until we have implemented them *****/

#define OUTCOME_HOMEWIN 1
#define OUTCOME_DRAW    2
#define OUTCOME_AWAYWIN 3
typedef struct _Date {
    int year;
    uint8_t month, day;
} Date;

struct _Game {
    int id; /* FIXME: Needed? */
    uint8_t outcome;
    Date date;
    int cachedPoints; /* Cached points. -1 indicates not cached yet */
    Team* homeTeam;
    Team* awayTeam;
};

#define MAX_TEAM_NAME 30
#define MAX_LOC_NAME  30
struct _Team {
    char name[MAX_TEAM_NAME];
    char location[MAX_LOC_NAME];
    GameList* gameList;
};
#endif /* DATATYPES_H */
