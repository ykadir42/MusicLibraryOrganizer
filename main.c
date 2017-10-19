//
// Created by kkyse on 10/17/2017.
//

#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "song_library.h"

#define DEBUG false

#define p(s) printf(s"\n")

#define pn() p("")

void debug_song_node() {
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

void debug_library() {
    p("creating library");
    struct song_library *const library = SongLibraryClass.new();
    p("created library");
    
    p("creating song1");
    const struct song song1 = SongClass.new("Title", "Artist");
    p("created song1");
    
    p("printing song1");
    song1.c->print(song1);
    p("printed song1");
    
    p("adding song1");
    library->c->add_song(library, song1);
    p("added song1");

//    library->c->add_song(library, SongClass.new("Hello", "World"));
//    library->c->add_song(library, SongClass.new("Khyber", "Sen"));
    
    library->c->add_songs_from_csv(library, "songs.csv");
    
    p("printing library");
    library->c->print(library);
    p("printed library");
    
    const struct song_node *node = library->c->songs_by_artist_letter(library, 'A');
    node->c->print(node);
    
    library->c->free(library);
    
}

void test_song_node() {

}

void test_song_library() {
    p("TESTING SONG LIBRARY\n");
    p("====================\n");
    
    PRE_SONG_STRING = "\t\t";
    
    p("Testing song_library constructor");
    struct song_library *const library = SongLibraryClass.new();
    pn();
    
    p("Testing song_library.add_songs_from_csv(),");
    p("\twhich tests song_library.add_song");
    library->c->add_songs_from_csv(library, "songs.csv");
    pn();
    
    p("Testing song_library.print(),");
    p("\tshould print all songs in alphabetic order by artist, then song name");
    library->c->print(library);
    pn();
    
    p("Testing song_library.print_by_letter('A'),");
    p("\tshould print all songs by 'A' in alphabetic order");
    library->c->print_by_letter(library, 'A');
    pn();
    
    p("Testing song_library.print_by_artist(\"Alz\"),");
    p("\tshould print all songs by \"Alz\" in alphabetic order");
    library->c->print_by_artist(library, "Alz");
    pn();
    
    library->c.fi
    
    p("Testing song_library.free()");
    library->c->free(library);
    pn();
}

int main() {
    srand((unsigned int) time(NULL));
    
    #if (DEBUG)
    debug_song_node();
    debug_library();
    #endif
    
    test_song_node();
    test_song_library();
    
    return EXIT_SUCCESS;
}