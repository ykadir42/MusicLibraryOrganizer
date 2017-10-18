//
// Created by kkyse on 10/16/2017.
//

#include "song.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

static inline char *new_strcpy(const char *const s) {
    char *const copy = (char *) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(copy, s);
    return copy;
}

struct song song_new(const char *const name, const char *const artist) {
    assert(name);
    assert(artist);
    assert(*name);
    assert(*artist);
    return (struct song) {.c = &SongClass, .name = new_strcpy(name), .artist = new_strcpy(artist)};
}

bool song_equals(const struct song this, const struct song song) {
    return strcmp(this.name, song.name) == 0 && strcmp(this.artist, song.artist) == 0;
}

int song_compare_to(const struct song this, const struct song song) {
    const int cmp = strcmp(this.artist, song.artist);
    if (cmp != 0) {
        return cmp;
    }
    return strcmp(this.name, song.name);
}

char *song_to_string(const struct song this) {
//    printf("to_stringing song\n");
    const size_t new_length = strlen(this.name) + strlen(" by ") + strlen(this.artist) + 100;
    char *const s = (char *) malloc((new_length + 1) * sizeof(char));
    sprintf(s, "%s by %s", this.name, this.artist);
//    printf("to_stringed song\n");
    return s;
}

void song_print(const struct song this) {
//    printf("printing song\n");
    char *const s = this.c->to_string(this);
    printf("%s\n", s);
    free(s);
//    printf("printed song\n");
}

void song_free(const struct song this) {
    free((char *) this.artist);
    free((char *) this.name);
}

const struct song_class SongClass = {
        &song_new,
        &song_equals,
        &song_compare_to,
        &song_to_string,
        &song_print,
        &song_free,
};