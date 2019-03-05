#include "../../include/json.h"
#include <stdio.h>
#include <stdlib.h>

int main ()
{
    FILE * legume = new_json("legume");

    float p = 45.788;
    int p2 = 2;

    open_json_obj(legume);

    write_json(legume,"nom","abricot",'s');
    write_json(legume,"poids",&p,'f');
    write_json(legume,"prix",&p2,'d');

    close_json_obj(legume);
    fclose(legume);
    return 0;
}