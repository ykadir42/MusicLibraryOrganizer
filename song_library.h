//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_LIBRARY_H
#define SYSTEMS_SONG_LIBRARY_H

#include "song_node.h"

struct song_library_class {
    
    struct song_library *(*const new)();
    
    struct song_node *(*const songs_by_artist_letter)(const struct song_library *const this, const char letter);
    
    void (*const add_song)(struct song_library *const this, const struct song song);
    
    int (*const add_songs_from_csv)(struct song_library *const this, const char *const filename);
    
    const struct song_node *(*const find_by_artist)(const struct song_library *const this, const char *const artist);
    
    const struct song_node *(*const find_by_name)(const struct song_library *const this, const char *const name);
    
    const struct song_node *(*const find_song)(const struct song_library *const this, const struct song song);
    
    void (*const print_by_letter)(const struct song_library *const this, const char letter);
    
    void (*const print_by_artist)(const struct song_library *const this, const char *const artist);
    
    void (*const print)(const struct song_library *const this);
    
    void (*const shuffle_and_print)(const struct song_library *const this, const size_t num_songs);
    
    void (*const remove_song)(struct song_library *const this, const struct song song);
    
    void (*const remove_all_songs)(struct song_library *const this);
    
    void (*const free)(struct song_library *const this);
    
};

#define SONG_TABLE_LENGTH 1 << (8 * sizeof(char))

struct song_library {
    
    const struct song_library_class *const c;
    struct song_node *table[SONG_TABLE_LENGTH]; // 256
    size_t lengths[SONG_TABLE_LENGTH];
    size_t num_songs;
    
};

extern const struct song_library_class SongLibraryClass;

#endif //SYSTEMS_SONG_LIBRARY_H
