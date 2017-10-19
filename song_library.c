//
// Created by kkyse on 10/16/2017.
//

#include <sys/types.h>

#include "song_library.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// TODO implement methods

#define membersize(type, member) (sizeof(((type *)0)->member))

#define arraysize(array) (sizeof(array) / sizeof(*(array)))

struct song_library *song_library_new() {
    const struct song_library local = {.c = &SongLibraryClass};
    struct song_library *dynamic = (struct song_library *) malloc(sizeof(struct song_library));
    memcpy(dynamic, &local, sizeof(struct song_library));
    return dynamic;
}

struct song_node *song_library_songs_by_artist_letter(const struct song_library *const this, const char letter) {
    return this->table[(unsigned char) letter];
}

void song_library_add_song(struct song_library *const this, const struct song song) {
    const size_t i = (unsigned char) *song.artist;
//    printf("i: %zu\n", i);
    struct song_node **const row_ptr = this->table + i;
    struct song_node *const row = *row_ptr;
    if (!row) {
//        printf("adding song to new linked list\n");
        *row_ptr = SongNodeClass.new(song, NULL);
    } else {
//        printf("adding song to existing linked list\n");
        *row_ptr = row->c->insert_in_order(row, song); // insert and update head in table
//        printf("%p\n", (*row_ptr)->c);
//        (*row_ptr)->c->print(*row_ptr);
    }
    this->lengths[i]++;
    this->num_songs++;
}

// needed b/c header not on school computers for some reason
// #include <sys/types.h> // done at top of file
ssize_t getline(char **lineptr, size_t *n, FILE *stream); // NOLINT

static inline void _make_LF(char *const line, const size_t length) {
    // stupid carriage return mess up everything
    if (line[length - 1] == '\r') {
        // getline() or other functions will probably fail if no '\n' at all anyways
        line[length - 1] = '\n'; // fix CR on old OS X
    }
    if (line[length - 2] == '\r') {
        line[length - 2] = 0; // fix CRLF on Windows
    }
}

int song_library_add_songs_from_csv(struct song_library *const this, const char *const filename) {
    FILE *const file = fopen(filename, "r");
    if (!file) {
        return -1;
    }
    for (size_t length = 0;;) {
        char *line = NULL;
        if (getline(&line, &length, file) < 0) {
            free(line);
            break;
        }
        _make_LF(line, length);
        const char *name = strtok(line, ",");
        const char *artist = strtok(NULL, "\n");
//        printf("_____________________\n");
//        printf("line: %s\n", line);
//        printf("adding song: %s by %s\n", name, artist);
//        printf("_____________________\n");
        this->c->add_song(this, SongClass.new(name, artist));
        free(line);
    }
    fclose(file);
    return EXIT_SUCCESS;
}

struct song song_library_find_by_name(const struct song_library *const this, const char *const name) {
    assert(name);
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        const struct song_node *const row = this->table[i];
        const struct song_node *const found = row->c->find_by_name(row, name);
        if (found) {
            return found->song;
        }
    }
    return (struct song) {0};
}

const struct song_node *song_library_find_by_artist(const struct song_library *const this, const char *const artist) {
    assert(artist);
    const struct song_node *const row = this->c->songs_by_artist_letter(this, *artist);
    if (!row) {
        return NULL;
    }
    return row->c->find_by_artist(row, artist);
}

void song_library_print_by_letter(const struct song_library *const this, const char letter) {
    const struct song_node *const row = this->c->songs_by_artist_letter(this, letter);
    if (row) {
        row->c->print(row);
    }
}

void song_library_print_by_artist(const struct song_library *const this, const char *const artist) {
    const struct song_node *cur = this->c->find_by_artist(this, artist);
    // alphabetized, so this is allowed (stopping when given artist isn't the current song anymore)
    for (; cur; cur = cur->next) {
        if (strcmp(artist, cur->song.artist) != 0) {
            break;
        }
        cur->song.c->print(cur->song);
    }
}

void song_library_print(const struct song_library *const this) {
//    for (size_t i = 0; i * 8 < sizeof(this->table); ++i) {
//        printf("%zu: %zu\n", i, ((size_t *) this->table)[i]);
//    }
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        const struct song_node *const row = this->table[i];
        if (row) {
//            printf("printing row %zu\n", i);
            row->c->print(row);
        }
    }
}

void song_library_shuffle_and_print(const struct song_library *const this, const size_t num_songs) {
    for (size_t i = 0; i < num_songs; ++i) {
        size_t rand_index = rand() % this->num_songs;
        for (size_t j = 0; j < arraysize(this->lengths); ++j) {
            const size_t index = this->lengths[j];
            if (rand_index < index) {
                const struct song_node *const row = this->table[j];
                struct song song = row->c->get(row, rand_index)->song;
                song.c->print(song);
                break;
            }
            rand_index -= index;
        }
    }
}

void song_library_remove_song(struct song_library *const this, const struct song song) {
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        struct song_node *const row = this->table[i];
        if (row) {
            this->table[i] = row->c->remove_song(row, song);
            this->lengths[i]--;
            this->num_songs--;
        }
    }
}

void song_library_remove_all_songs(struct song_library *const this) {
    for (size_t i = 0; i < arraysize(this->table); ++i) {
        struct song_node *const row = this->table[i];
        if (row) {
            row->c->free(row);
        }
    }
    memset(this->table, 0, sizeof(this->table));
    memset(this->lengths, 0, sizeof(this->lengths));
    this->num_songs = 0;
}

void song_library_free(struct song_library *const this) {
    this->c->remove_all_songs(this);
    free(this);
}

const struct song_library_class SongLibraryClass = {
        &song_library_new,
        &song_library_songs_by_artist_letter,
        &song_library_add_song,
        &song_library_add_songs_from_csv,
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