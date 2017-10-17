//
// Created by kkyse on 10/16/2017.
//

#include "song_library.h"

// TODO implement methods

#define membersize(type, member) (sizeof(((type *)0)->member))

#define arraysize(array) (sizeof(array) / sizeof(*(array)))

struct song_library *song_library_new() {
    struct song_library *dynamic = (struct song_library *) calloc(NULL, sizeof(struct song_library));
    memcpy((struct song_library_class *) &dynamic->c, &SongLibraryClass, membersize(struct song_library, c));
    return dynamic;
}

void song_library_add_song(struct song_library *const this, const struct song song) {
    struct song_node **const row_ptr = this->table + *song.artist;
    struct song_node *const row = *row_ptr;
    if (!row) {
        *row_ptr = SongNodeClass.new(song, NULL);
    } else {
        *row_ptr = row->c.insert_in_order(row, song); // insert and update head in table
    }
}

struct song song_library_find_by_name(const struct song_library *const this, const char *const name) {
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        const struct song_node *const row = this->table[i];
        const struct song song = row->c.find_by_name(row, name);
        if (memcmp(&song, &(struct song) {}, sizeof(struct song)) != 0) {
            return song;
        }
    }
    return {};
}

struct song song_library_find_by_artist(const struct song_library *const this, const char *const artist) {
    assert(artist);
    const struct song_node *const row = this->table[*artist];
    if (!row) {
        return {};
    }
    return row->c.find_by_artist(row, artist);
}

void song_library_print_by_letter(const struct song_library *const this, const char letter);

void song_library_print_by_artist(const struct song_library *const this, const char *const artist);

void song_library_print(const struct song_library *const this);

void song_library_shuffle_and_print(const struct song_library *const this);

void song_library_remove_song(struct song_library *const this, const struct song song);

void song_library_remove_all_songs(struct song_library *const this) {
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        struct song_node *const row = this->table[i];
        if (row) {
            row->c.free(row);
        }
    }
    memset(this->table, 0, sizeof(this->table));
}

void song_library_free(struct song_library *const this) {
    this->c.remove_all_songs(this);
    free(this);
}

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