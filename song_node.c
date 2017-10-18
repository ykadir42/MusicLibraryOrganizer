//
// Created by kkyse on 10/16/2017.
//

#include "song_node.h"

#include <stdlib.h>
#include <string.h>

struct song_node *song_node_new(const struct song song, const struct song_node *const next) {
    const struct song_node local = {.c = &SongNodeClass, .song = song, .next = (struct song_node *const) next};
    struct song_node *dynamic = (struct song_node *) malloc(sizeof(struct song_node));
    memcpy(dynamic, &local, sizeof(struct song_node));
    return dynamic;
}

size_t song_node_length(const struct song_node *this) {
    size_t i = 0;
    for (; this; ++i, this = this->next);
    return i;
}

struct song_node *song_node_insert_front(const struct song_node *const this, const struct song song) {
    return SongNodeClass.new(song, this);
}

struct song_node *song_node_insert_in_order(const struct song_node *const this, const struct song song) {
    for (struct song_node *cur = (struct song_node *) this; cur; cur = cur->next) {
        if (song.c->compare_to(song, cur->song) < 0) {
            if (cur == this) {
                return this->c->insert_front(this, song);
            } else {
                if (cur->next) {
                    cur->next = cur->next->c->insert_front(cur->next, song);
                } else {
                    cur->next = SongNodeClass.new(song, NULL);
                }
                return (struct song_node *) this;
            }
        }
        if (!cur->next) { // at end
            cur->next = SongNodeClass.new(song, NULL);
            return (struct song_node *) this;
        }
    }
    return NULL; // UNREACHABLE
}

void song_node_print(const struct song_node *this) {
    for (;this ; this = this->next) {
        this->song.c->print(this->song);
    }
}

#define find_by_(str_field) \
const struct song_node *song_node_find_by_##str_field(const struct song_node *this, const char *const str_field) { \
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

const struct song_node *song_node_get(const struct song_node *this, const size_t index) {
    for (size_t i = 0; i < index && this; ++i, this = this->next);
    return this;
}

const struct song_node *song_node_get_random_with_length(const struct song_node *this, const size_t length) {
    return this->c->get(this, rand() % length);
}

const struct song_node *song_node_get_random(const struct song_node *this) {
    return this->c->get_random_with_length(this, this->c->length(this));
}

struct song_node *song_node_remove_front(struct song_node *this) {
    struct song_node *const next = this->next;
    free(this);
    return next;
}

struct song_node *song_node_remove_song(struct song_node *const this, const struct song song) {
    for (struct song_node *cur = this, *prev = NULL; cur; prev = cur, cur = cur->next) {
        if (cur->song.c->equals(cur->song, song)) {
            if (cur == this) {
                return this->c->remove_front(this);
            } else {
                prev->next = cur->next;
                free(cur);
                return this;
            }
        }
    }
    return NULL; // UNREACHABLE
}

struct song_node *song_node_free(struct song_node *this) {
    for (;;) {
        struct song_node *const next = this->next;
        this->song.c->free(this->song);
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
        &song_node_get_random_with_length,
        &song_node_get_random,
        &song_node_remove_front,
        &song_node_remove_song,
        &song_node_free,
};