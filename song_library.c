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

struct song_node *song_library_songs_by_letter(const struct song_library *const this, const char letter) {
    return this->table[(unsigned char) letter];
}

void song_library_add_song(struct song_library *const this, const struct song song) {
    struct song_node **const row_ptr = this->table + (unsigned char) *song.artist;
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
    const struct song_node *const row = this->c.songs_by_letter(this, *artist);
    if (!row) {
        return {};
    }
    return row->c.find_by_artist(row, artist);
}

void song_library_print_by_letter(const struct song_library *const this, const char letter) {
    const struct song_node *const row = this->c.songs_by_letter(this, letter);
    if (row) {
        row->c.print(row);
    }
}

void song_library_print_by_artist(const struct song_library *const this, const char *const artist) {
    const struct song_node *cur = this->c.songs_by_letter(this, *artist);
    for (; cur; cur = cur->next) {
        if (strcmp(artist, cur->song.artist) == 0) {
            break;
        }
    }
    // alphabetized, so this is allowed (stopping when given artist isn't the current song anymore)
    for (; cur; cur = cur->next) {
        if (strcmp(artist, cur->song.artist) != 0) {
            break;
        }
        cur->song.c.print(cur->song);
    }
}

void song_library_print(const struct song_library *const this) {
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        const struct song_node *const row = this->table[i];
        if (row) {
            row->c.print(row);
        }
    }
}

void song_library_shuffle_and_print(const struct song_library *const this) {
    // TODO
}

void song_library_remove_song(struct song_library *const this, const struct song song) {
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        struct song_node *const row = this->table[i];
        if (row) {
            this->table[i] = row->c.remove_song(row, song);
        }
    }
}

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
        &song_library_songs_by_letter,
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