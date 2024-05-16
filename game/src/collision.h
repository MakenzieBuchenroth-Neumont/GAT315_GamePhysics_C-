#pragma once
#include "raylib.h"

typedef struct nkContact nkContact_t;
typedef struct nkBody nkBody;

void createContacts(nkBody* bodies, nkContact_t** contacts);
nkContact_t* generateContact(nkBody* body1, nkBody* body2);

void separateContacts(nkContact_t* contacts);
void resolveContacts(nkContact_t* contacts);