//
// Created by kkyse on 10/16/2017.
//

#include "song.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct song song_new(const char *const name, const char *const artist) {
    return {.c = SongClass, .name = name, .artist = artist};
}

bool song_equals(const struct song this, const struct song song) {
    return strcmp(this.name, song.name) == 0 && strcmp(this.artist, song.artist);
}

char *song_to_string(const struct song this) {
    const size_t new_length = strlen(this.name) + strlen(" by ") + strlen(this.artist);
    char *const s = (char *) malloc((new_length + 1) * sizeof(char));
    sprintf(s, "%s by %s", this.name, this.artist);
}

const struct song_class SongClass = {
        &song_new,
        &song_to_string,
};