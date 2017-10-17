//
// Created by kkyse on 10/17/2017.
//

#include "main.h"

#include "song_library.h"

int main() {
    struct song_library *const library = SongLibraryClass.new();
    
    library->c.add_song(library, SongClass.new("Title", "Artist"));
    
    library->c.print(library);
    
    return 0;
}
