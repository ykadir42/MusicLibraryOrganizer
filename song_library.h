//
// Created by kkyse on 10/16/2017.
//

#ifndef SYSTEMS_SONG_LIBRARY_H
#define SYSTEMS_SONG_LIBRARY_H

#include "song_node.c"

struct song_library {
    struct song_node *const table['z' - 'a' + 1];
};



#endif //SYSTEMS_SONG_LIBRARY_H
