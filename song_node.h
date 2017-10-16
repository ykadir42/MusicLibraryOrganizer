//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_NODE_H
#define SYSTEMS_SONG_NODE_H

#include <stddef.h>

struct song {
    const char *const name;
    const char *const artist;
};

struct song_node {
    const struct song;
    struct song_node *next;
};

struct song_node *insert_front(struct song_node *songs, const struct song);

struct song_node *insert_in_order(struct song_node *songs, const struct song);

void *print_songs(struct song_node *songs);

struct song_node *find_by_name(struct song_node *songs, const char *const name);

struct song_node *find_by_artist(struct song_node *songs, const char *const artists);

struct song_node *get(struct song_node *songs, const size_t index);

struct song_node *get_random(struct song_node *songs);

struct song_node *remove_front(struct song_node *songs);

struct song_node *remove_song(struct song_node *songs, const struct song);

struct song_node *free_songs(struct song_node *songs);

#endif //SYSTEMS_SONG_NODE_H
