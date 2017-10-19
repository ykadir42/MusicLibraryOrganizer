//
// Created by kkyse on 10/16/2017.
//

#include "song.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

const char *PRE_SONG_STRING = "";

static inline char *new_strcpy(const char *const s) {
    char *const copy = (char *) malloc((strlen(s) + 1) * sizeof(char));
    strcpy(copy, s);
//    printf("%s\n", s);
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
    return this.c->compare_to(this, song) == 0;
}

#define is_Alessia(s) ((s)[0] == 'A' && (s)[1] == 'l')

int song_compare_to(const struct song this, const struct song song) {
    const int cmp = strcmp(this.artist, song.artist);
    #if (DEBUG)
    //    const bool is_Alessia = strcmp(song.artist, "Alessia Cara") == 0;
        if (is_Alessia(song.artist) || is_Alessia(this.artist)) {
            printf("maybe\n");
        }
        for (int i = 0; i < strlen(this.artist); i++) {
            printf("%d, ", this.artist[i]);
        }
        printf("\n[%s}\n", this.artist);
        printf("[%s}\n", song.artist);
        printf("%d\n\n", cmp);
    //    printf("[%s] vs [%s]: %d\n", this.artist, song.artist, cmp);
    #endif
    if (cmp != 0) {
        return cmp;
    }
    #if (DEBUG)
    printf("\ncmp by name\n");
    printf("[%s]\n", this.name);
    printf("[%s]\n", song.name);
    printf("%d\n\n", strcmp(this.name, song.name));
    #endif
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
    printf(PRE_SONG_STRING);
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