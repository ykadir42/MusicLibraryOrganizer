//
// Created by kkyse on 10/17/2017.
//

#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>

#include "song_library.h"

#define DEBUG false

#define p(s) printf(s"\n")

#define pn() p("")

void debug_SongNode() {
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

void debug_SongLibrary() {
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

void test_SongNode() {

}

void test_SongLibrary() {
    p("TESTING SONG LIBRARY\n");
    p("====================\n");
    
    PRE_SONG_STRING = "\t\t";
    
    p("Testing song_library constructor");
    SongLibrary *const library = SongLibraryClass.new();
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
    
    p("Testing song_library.find_song(),");
    p("\twhich uses song_library.find_by_artist() and song_library.find_by_name()");
    const Song song = SongClass.new("Cheap Thrills", "Sia");
    char *const song_str1 = song.c->to_string(song);
    printf("\tFinding song %s...\n", song_str1);
    const Song found_song = library->c->find_song(library, song)->song;
    char *const song_str2 = found_song.c->to_string(found_song);
    printf("\tFound song %s\n", song_str2);
    free(song_str2);
    pn();
    
    const uint32_t num_repeats = 0;
    for (uint32_t i = 0; i < num_repeats; ++i) {
        library->c->add_songs_from_csv(library, "songs.csv");
    }
    
    p("Testing song_library.shuffle_and_print() for 10 random songs");
    library->c->shuffle_and_print(library, 10);
    p("\tHopefully these are all random.");
    p("\tTesting for the correct random distribution would be much harder.");
    pn();
    
    if (num_repeats > 0) {
        library->c->print(library);
    }
    
    
    p("Testing song_library.remove_song()");
    p("\tprinting library before removal...");
    library->c->print(library);
    library->c->remove_song(library, song);
    printf("\tprinting library again to make sure %s was removed...\n", song_str1);
    library->c->print(library);
    p("\tIt might be hard to check if it was removed,");
    printf("\tso now printing all songs by letter '%c' from %s...\n", *song.artist, song_str1);
    library->c->print_by_letter(library, *song.artist);
    pn();
    
    song.c->free(song);
    free(song_str1);
    
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
    
    test_SongNode();
    test_SongLibrary();
    
    return EXIT_SUCCESS;
}