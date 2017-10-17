//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_H
#define SYSTEMS_SONG_H

#include <stdbool.h>

struct song_class {
    
    struct song (*const new)(const char *const name, const char *const artist);
    
    bool (*const equals)(const struct song this, const struct song song);
    
    char *(*const to_string)(const struct song this);
    
};

struct song {
    
    const struct song_class c;
    
    const char *const name;
    const char *const artist;
    
};

extern const struct song_class SongClass;

#endif //SYSTEMS_SONG_H
