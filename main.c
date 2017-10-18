//
// Created by kkyse on 10/17/2017.
//

#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "song_library.h"

#define p(s) printf(s"\n");

void test_song_node() {
    typedef struct song_node SongNode;
    typedef struct song Song;
    
    Song song1 = SongClass.new("Name", "Artists");
    Song song2 = SongClass.new("Hello", "World");
    //Song song3 = SongClass.new("Song", "Bob");
    
    p("inserting in order");
    
    SongNode *node = SongNodeClass.new(song1, NULL);
    node = node->c->insert_in_order(node, song2);
    printf("%p\n", node);
    //node = node->c->insert_in_order(node, song3);
    node->c->print(node);
    
    node->c->free(node);
}

void test_library() {
    srand((unsigned int) time(NULL));
    
    p("creating library")
    struct song_library *const library = SongLibraryClass.new();
    p("created library");
    
    p("creating song1");
    const struct song song1 = SongClass.new("Title", "Artist");
    p("created song1")
    
    p("printing song1");
    song1.c->print(song1);
    p("printed song1");
    
    p("adding song1");
    library->c->add_song(library, song1);
    p("added song1");
    
    const struct song_node *node = library->c->songs_by_letter(library, 'A');
    printf("%p\n", node);
    const struct song song2 = node->song;
    song2.c->print(song2);

//    library->c->add_song(library, SongClass.new("Hello", "World"));
//    library->c->add_song(library, SongClass.new("Khyber", "Sen"));
    
    library->c->add_songs_from_csv(library, "songs.csv");
    
    p("printing library");
    library->c->print(library);
    p("printed library");
    
    
    
    
    
    library->c->free(library);
}

int main() {
    test_song_node();
    
    test_library();
    
    return EXIT_SUCCESS;
}
