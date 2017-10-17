//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_LIBRARY_H
#define SYSTEMS_SONG_LIBRARY_H

#include "song_node.c"

struct song_library_class {
    
    struct song_library *(*const new)();
    
    void (*const add_song)(struct song_library *const song_library, const struct song song);
    
    struct song (*const find_by_name)(struct song_library *const song_library, const char *const name);
    
    struct song (*const find_by_artist)(struct song_library *const song_library, const char *const artist);
    
    void (*const print_by_letter)(struct song_library *const song_library, const char letter);
    
    void (*const print_by_artist)(struct song_library *const song_library, const char *const artist);
    
    void (*const print)(struct song_library *const song_library);
    
    void (*const shuffle_and_print)(struct song_library *const song_library);
    
    void (*const remove_song)(struct song_library *const song_library, const struct song song);
    
    void (*const remove_all_songs)(struct song_library *const song_library);
    
    void (*const free)(struct song_library *const song_library);
    
};

struct song_library {
    const struct song_library_class c;
    struct song_node *table['z' - 'a' + 1];
};

extern const struct song_library_class SongLibraryClass;

#endif //SYSTEMS_SONG_LIBRARY_H
