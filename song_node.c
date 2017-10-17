//
// Created by kkyse on 10/16/2017.
//

#include "song_node.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct song_node *song_node_new(const struct song song, struct song_node *const next) {
    const struct song_node local = {.c = SongNodeClass, .song = song, .next = next};
    struct song_node *dynamic = (struct song_node *) malloc(sizeof(struct song_node));
    memcpy(dynamic, &local, sizeof(struct song_node));
    return dynamic;
}

size_t song_node_length(const struct song_node *this) {
    size_t i = 0;
    for (; this; ++i, this = this->next);
    return i;
}

struct song_node *song_node_insert_front(const struct song_node *this, const struct song song) {
    struct song_node *const front = (struct song_node *) malloc(sizeof(struct song_node));
    front->song = song;
    front->next = (struct song_node *) this;
    return front;
}

struct song_node *song_node_insert_in_order(struct song_node *this, const struct song song);

void song_node_print(struct song_node *this) {
    for (;this ; this = this->next) {
        printf("%s\n", this->song.c.to_string(this->song));
    }
}

#define find_by_(str_field) \
struct song_node *song_node_find_by_##str_field(struct song_node *this, const char *const str_field) { \
    for (; this; this = this->next) { \
        if (strcmp(str_field, this->song.str_field) == 0) { \
            return this; \
        } \
    } \
    return NULL; \
}

find_by_(name)

find_by_(artist)

#undef find_by_

struct song_node *song_node_get(struct song_node *this, const size_t index) {
    for (size_t i = 0; i < index && this; ++i, this = this->next);
    return this;
}

struct song_node *song_node_get_random(struct song_node *this) {
    return this->c.get(this, rand() % this->c.length(this));
}

struct song_node *song_node_remove_front(struct song_node *this) {
    struct song_node *const next = this->next;
    free(this);
    return next;
}

struct song_node *song_node_remove_song(struct song_node *const this, const struct song song) {
    for (struct song_node *cur = this, *prev = NULL; cur; prev = cur, cur = cur->next) {
        if (cur->song.c.equals(cur->song, song)) {
            if (cur == this) {
                return this->c.remove_front(this);
            } else {
                prev->next = cur->next;
                free(cur);
                return this;
            }
        }
    }
}

struct song_node *song_node_free(struct song_node *this) {
    for (;;) {
        struct song_node *const next = this->next;
        free(this);
        if (!next) {
            return NULL;
        }
        this = next;
    }
}

const struct song_node_class SongNodeClass = {
        &song_node_new,
        &song_node_length,
        &song_node_insert_front,
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