//
// Created by kkyse on 10/16/2017.
//

#include "song_node.h"

#include <stdlib.h>
#include <string.h>

// TODO implement methods

struct song_node *insert_front(struct song_node *songs, const struct song song);

struct song_node *song_node_insert_in_order(struct song_node *songs, const struct song song);

void song_node_print(struct song_node *songs);

struct song_node *song_node_find_by_name(struct song_node *songs, const char *const name);

struct song_node *song_node_find_by_artist(struct song_node *songs, const char *const artists);

struct song_node *song_node_get(struct song_node *songs, const size_t index);

struct song_node *song_node_get_random(struct song_node *songs);

struct song_node *song_node_remove_front(struct song_node *songs);

struct song_node *song_node_remove_song(struct song_node *songs, const struct song song);

struct song_node *song_node_free(struct song_node *songs);

const struct song_node_class SongNodeClass = {
        &insert_front,
        &song_node_insert_in_order,
        &song_node_print,
        &song_node_find_by_name,
        &song_node_find_by_artist,
        &song_node_get,
        &song_node_get_random,
        &song_node_remove_front,
        &song_node_remove_song,
        &song_node_free,
};

struct song_node *new_song_node(const struct song song, struct song_node *const next) {
    const struct song_node local = {.c = SongNodeClass, .song = song, .next = next};
    struct song_node *dynamic = (struct song_node *) malloc(sizeof(struct song_node));
    memcpy(dynamic, &local, sizeof(struct song_node));
    return dynamic;
}