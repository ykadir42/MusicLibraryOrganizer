//
// Created by kkyse on 10/16/2017.
//

#include "song_library.h"

// TODO implement methods

void init_song_library(struct song_node **const table) {
    // TODO
}

struct song_library *song_library_new() {
    const struct song_library local = {.c = SongLibraryClass};
    init_song_library(local.table);
    struct song_library *dynamic = (struct song_library *) malloc(sizeof(struct song_library));
    memcpy(dynamic, &local, sizeof(struct song_library));
    return dynamic;
}

void song_library_add_song(struct song_library *const this, const struct song song);

struct song song_library_find_by_name(struct song_library *const this, const char *const name);

struct song song_library_find_by_artist(struct song_library *const this, const char *const artist);

void song_library_print_by_letter(struct song_library *const this, const char letter);

void song_library_print_by_artist(struct song_library *const this, const char *const artist);

void song_library_print(struct song_library *const this);

void song_library_shuffle_and_print(struct song_library *const this);

void song_library_remove_song(struct song_library *const this, const struct song song);

void song_library_remove_all_songs(struct song_library *const this);

void song_library_free(struct song_library *const this);

const struct song_library_class SongLibraryClass = {
        &song_library_new,
        &song_library_add_song,
        &song_library_find_by_name,
        &song_library_find_by_artist,
        &song_library_print_by_letter,
        &song_library_print_by_artist,
        &song_library_print,
        &song_library_shuffle_and_print,
        &song_library_remove_song,
        &song_library_remove_all_songs,
        &song_library_free,
};