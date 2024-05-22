#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

//ncContact_t* ncContacts = NULL;

void addContact(nkContact_t* contact, nkContact_t** contacts)
{
	assert(contact);

	// add element to linked list
	contact->next = *contacts;

	// set head of elements to new element
	*contacts = contact;
}

void destroyAllContacts(nkContact_t** contacts) {
	if (!contacts) return;
	if (!*contacts) return;

	nkContact_t* contact = *contacts;
	while (contact)
	{
		nkContact_t* next = contact->next;
		free(contact);
		contact = next;
	}

	*contacts = NULL;
}