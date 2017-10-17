//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_NODE_H
#define SYSTEMS_SONG_NODE_H

#include <stddef.h>

#include "song.h"

struct song_node_class {
    
    struct song_node *(*const new)(const struct song song, struct song_node *const next);
    
    size_t (*const length)(const struct song_node *this);
    
    struct song_node *(*const insert_front)(const struct song_node *const this, const struct song song);
    
    struct song_node *(*const insert_in_order)(const struct song_node *this, const struct song song);
    
    void (*const print)(const struct song_node *this);
    
    struct song (*const find_by_name)(const struct song_node *this, const char *const name);
    
    struct song (*const find_by_artist)(const struct song_node *this, const char *const artist);
    
    struct song_node *(*const get)(const struct song_node *this, const size_t index);
    
    struct song_node *(*const get_random)(const struct song_node *this);
    
    struct song_node *(*const remove_front)(struct song_node *this);
    
    struct song_node *(*const remove_song)(struct song_node *const this, const struct song);
    
    struct song_node *(*const free)(struct song_node *this);
    
};

struct song_node {
    
    const struct song_node_class c;
    struct song song;
    struct song_node *next;
    
};

extern const struct song_node_class SongNodeClass;

#endif //SYSTEMS_SONG_NODE_H
