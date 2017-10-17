//
// Created by kkyse on 10/16/2017.
//

#include "song.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

struct song song_new(const char *const name, const char *const artist) {
    assert(name);
    assert(artist);
    assert(*name);
    assert(*artist);
    return {.c = SongClass, .name = name, .artist = artist};
}

bool song_equals(const struct song this, const struct song song) {
    return strcmp(this.name, song.name) == 0 && strcmp(this.artist, song.artist);
}

int song_compare_to(const struct song this, const struct song song) {
    const int cmp = strcmp(this.artist, song.artist);
    if (cmp != 0) {
        return cmp;
    }
    return strcmp(this.name, song.name);
}

char *song_to_string(const struct song this) {
    const size_t new_length = strlen(this.name) + strlen(" by ") + strlen(this.artist);
    char *const s = (char *) malloc((new_length + 1) * sizeof(char));
    sprintf(s, "%s by %s", this.name, this.artist);
}

void print(const struct song this) {
    char *const s = this.c.to_string(this);
    printf("%s\n", s);
    free(s);
}

const struct song_class SongClass = {
        &song_new,
        &song_equals,
        &song_compare_to,
        &song_to_string,
};