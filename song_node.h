//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_NODE_H
#define SYSTEMS_SONG_NODE_H

#include <stddef.h>

struct song_node_class {
    
    struct song_node *(*const insert_front)(struct song_node *songs, const struct song song);
    
    struct song_node *(*const insert_in_order)(struct song_node *songs, const struct song song);
    
    void (*const print)(struct song_node *songs);
    
    struct song_node *(*const find_by_name)(struct song_node *songs, const char *const name);
    
    struct song_node *(*const find_by_artist)(struct song_node *songs, const char *const artists);
    
    struct song_node *(*const get)(struct song_node *songs, const size_t index);
    
    struct song_node *(*const get_random)(struct song_node *songs);
    
    struct song_node *(*const remove_front)(struct song_node *songs);
    
    struct song_node *(*const remove_song)(struct song_node *songs, const struct song);
    
    struct song_node *(*const free)(struct song_node *songs);
    
};

struct song {
    
    const char *const name;
    const char *const artist;
    
};

struct song_node {
    
    const struct song_node_class c;
    const struct song song;
    struct song_node *next;
    
};

extern const struct song_node_class SongNodeClass;

struct song_node *new_song_node(const struct song song, struct song_node *const next);

#endif //SYSTEMS_SONG_NODE_H
