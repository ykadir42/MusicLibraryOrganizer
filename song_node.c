//
// Created by kkyse on 10/16/2017.
//

#include "song_node.h"

#include <stdlib.h>
#include <string.h>

SongNode *SongNode_new(const Song song, const SongNode *const next) {
    const SongNode local = {.c = &SongNodeClass, .song = song, .next = (SongNode *const) next};
    SongNode *dynamic = (SongNode *) malloc(sizeof(SongNode));
    memcpy(dynamic, &local, sizeof(SongNode));
    return dynamic;
}

size_t SongNode_length(const SongNode *this) {
    size_t i = 0;
    for (; this; ++i, this = this->next);
    return i;
}

SongNode *SongNode_insert_front(const SongNode *const this, const Song song) {
    return SongNodeClass.new(song, this);
}

SongNode *SongNode_insert_in_order(const SongNode *const this, const Song song) {
    #if (DEBUG)
    const bool is_A = *song.artist == 'A';
    if (is_A) {
        printf("A: ");
        song.c->print(song);
    }
    printf("inserting in order\n");
        #define SongName(when) if (song.name[0] == 'S') printf("inserting "#when"\n")
    #endif
    for (SongNode *prev = NULL, *cur = (SongNode *) this; cur; prev = cur, cur = cur->next) {
        if (song.c->compare_to(song, cur->song) < 0) {
            if (!prev) {
                #if (DEBUG)
                SongName(front);
                #endif
                return this->c->insert_front(this, song);
            } else {
                if (prev->next) {
                    #if (DEBUG)
                    SongName(middle);
                    #endif
                    prev->next = cur->c->insert_front(cur, song);
                } else {
                    #if (DEBUG)
                    SongName(end);
                    #endif
                    cur->next = SongNodeClass.new(song, NULL);
                }
                return (SongNode *) this;
            }
        }
        if (!cur->next) { // at end
            cur->next = SongNodeClass.new(song, NULL);
            return (SongNode *) this;
        }
    }
    return NULL; // UNREACHABLE
}

void SongNode_print(const SongNode *this) {
    for (; this; this = this->next) {
        this->song.c->print(this->song);
    }
}

#define find_by_(str_field) \
const SongNode *SongNode_find_by_##str_field(const SongNode *this, const char *const str_field) { \
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

const SongNode *SongNode_get(const SongNode *this, const size_t index) {
    for (size_t i = 0; i < index && this; ++i, this = this->next);
    return this;
}

const SongNode *SongNode_get_random_with_length(const SongNode *this, const size_t length) {
    return this->c->get(this, rand() % length);
}

const SongNode *SongNode_get_random(const SongNode *this) {
    return this->c->get_random_with_length(this, this->c->length(this));
}

SongNode *SongNode_remove_front(SongNode *this) {
    SongNode *const next = this->next;
    free(this);
    return next;
}

SongNode *SongNode_remove_song(SongNode *const this, const Song song) {
    for (SongNode *cur = this, *prev = NULL; cur; prev = cur, cur = cur->next) {
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

SongNode *SongNode_free(SongNode *this) {
    for (;;) {
        SongNode *const next = this->next;
        this->song.c->free(this->song);
        free(this);
        if (!next) {
            return NULL;
        }
        this = next;
    }
}

const struct song_node_class SongNodeClass = {
        &SongNode_new,
        &SongNode_length,
        &SongNode_insert_front,
        &SongNode_insert_in_order,
        &SongNode_print,
        &SongNode_find_by_name,
        &SongNode_find_by_artist,
        &SongNode_get,
        &SongNode_get_random_with_length,
        &SongNode_get_random,
        &SongNode_remove_front,
        &SongNode_remove_song,
        &SongNode_free,
};