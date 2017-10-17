//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_LIBRARY_H
#define SYSTEMS_SONG_LIBRARY_H

#include "song_node.c"

struct song_library_class {
    
    struct song_library *(*const new)();
    
    struct song_node *(*const songs_by_letter)(const struct song_library *const this, const char letter);
    
    void (*const add_song)(struct song_library *const this, const struct song song);
    
    struct song (*const find_by_name)(const struct song_library *const this, const char *const name);
    
    struct song (*const find_by_artist)(const struct song_library *const this, const char *const artist);
    
    void (*const print_by_letter)(const struct song_library *const this, const char letter);
    
    void (*const print_by_artist)(const struct song_library *const this, const char *const artist);
    
    void (*const print)(const struct song_library *const this);
    
    void (*const shuffle_and_print)(const struct song_library *const this);
    
    void (*const remove_song)(struct song_library *const this, const struct song song);
    
    void (*const remove_all_songs)(struct song_library *const this);
    
    void (*const free)(struct song_library *const this);
    
};

struct song_library {
    const struct song_library_class c;
    struct song_node *table[1 << sizeof(char)]; // 256
};

extern const struct song_library_class SongLibraryClass;

#endif //SYSTEMS_SONG_LIBRARY_H
