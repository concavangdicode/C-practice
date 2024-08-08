// Replace your main() with main_tests() to run the tests.

// Or, compile the contacts program with this main using:
// cat contacts.c a2_tests.c | clang -xc -e_main_tests -DNDEBUG -Wall -

// Do **not** submit this code in the same file as your solution.
// The markers will test your work by compiling it with the line above.

// Note that these tests do not verify sorting, printed list ordering or numbering, or the range of IDs

#define VERIFY(e,t) verify(e, t, #t)
#define VERIFY_NON_NEGATIVE(t) verify_non_negative(t, #t)


int Tests_Passed = 0;
int Tests_Failed = 0;

void verify(int expected, int result, char test[]) {
  if (expected == result) {
    printf("Passed: expected %d, got %d for: %s\n", expected, result, test);
    Tests_Passed++;
  } else {
    printf("FAILED: expected %d, got %d for: %s\n", expected, result, test);
    Tests_Failed++;
  }
}

void verify_non_negative(int result, char test[]) {
  if (result >= 0) {
    printf("Passed: expected non-negative, got %d for: %s\n", result, test);
    Tests_Passed++;
  } else {
    printf("FAILED: expected non-negative, got %d for: %s\n", result, test);
    Tests_Failed++;
  }
}

void test_empty_list() {
  printf("\n*** Testing empty list:\n");

  VERIFY(0, count_contacts());
  VERIFY(-1, count_contact_numbers(0));
  VERIFY(-1, count_contact_numbers(1));
  VERIFY(0, count_all_numbers());
  
  VERIFY(FALSE, delete_contact(0));
  VERIFY(FALSE, delete_contact(1));
  VERIFY(FALSE, remove_phone(0, ""));
  VERIFY(FALSE, remove_phone(1, ""));
}

void test_simple_list() {
  int contact1, contact2, contact3;
  printf("\n*** Testing a simple list:\n");
  
  VERIFY_NON_NEGATIVE(contact1 = new_contact("ghi", "xyz"));
  VERIFY_NON_NEGATIVE(contact2 = new_contact("abc def", "xyz"));

  VERIFY(TRUE, add_phone(contact1, 204, 5555555, "work"));
  VERIFY(TRUE, add_phone(contact2, 555, 5555556, "work"));
  VERIFY(TRUE, add_phone(contact2, 555, 5555556, "home office"));
  VERIFY(TRUE, add_phone(contact2, 555, 5555557, "work"));

  VERIFY_NON_NEGATIVE(contact3 = new_contact("jklm nop", ""));

  VERIFY(TRUE, add_phone(contact3, 204, 5555555, "work"));
  VERIFY(TRUE, add_phone(contact3, 204, 5555558, ""));
  VERIFY(TRUE, add_phone(contact1, 999, 9999999, "work"));
  VERIFY(TRUE, add_phone(contact1, 204, 5555559, "mobile"));

  // already added
  VERIFY(-1, new_contact("ghi", ""));
  
  VERIFY(3, count_contacts());
  VERIFY(8, count_all_numbers());
  VERIFY(3, count_contact_numbers(contact1));
  VERIFY(3, count_contact_numbers(contact2));
  VERIFY(2, count_contact_numbers(contact3));
  
  // this isn't an automated test since there's no way to verify:
  printf("\nExecuting print_contacts(TRUE):\n");
  print_contacts(TRUE);
  printf("\nExecuting print_contacts(FALSE):\n");
  print_contacts(FALSE);
  printf("\n");
  
  // this test is "fragile" as it could fail for reasons out of our control:
  VERIFY(TRUE, save_contacts("test_out.txt"));

  // manipulate the list
  VERIFY(TRUE, remove_phone(contact2, "home office"));
  VERIFY(FALSE, remove_phone(contact2, "mobile"));
  VERIFY(TRUE, remove_phone(contact1, "work")); // removes both!
  VERIFY(FALSE, remove_phone(contact1, "work"));
  VERIFY(5, count_all_numbers());
  VERIFY(1, count_contact_numbers(contact1));
  VERIFY(2, count_contact_numbers(contact2));
  
  VERIFY(TRUE, delete_contact(contact1));

  VERIFY(2, count_contacts());
  VERIFY(4, count_all_numbers());

  // can't use a non-existent contact:
  VERIFY(FALSE, add_phone(contact1, 204, 5555555, "work"));
  VERIFY(FALSE, remove_phone(contact1, "mobile"));
  VERIFY(-1, count_contact_numbers(contact1));

  VERIFY(TRUE, add_phone(contact3, 204, 5555555, "work"));

  VERIFY(TRUE, remove_phone(contact3, ""));
  VERIFY(4, count_all_numbers());
  VERIFY(TRUE, remove_phone(contact3, "work"));
  
  VERIFY_NON_NEGATIVE(contact1 = new_contact("qr stuvw", "xyz"));
  VERIFY(TRUE, add_phone(contact1, 204, 5555555, "work phone"));
  VERIFY(TRUE, add_phone(contact1, 204, 5555555, "work"));
  VERIFY(FALSE, remove_phone(contact1, "work mobile"));
  VERIFY(TRUE, remove_phone(contact1, "work"));

  VERIFY(3, count_all_numbers());
  VERIFY(1, count_contact_numbers(contact1));
  VERIFY(2, count_contact_numbers(contact2));
  VERIFY(0, count_contact_numbers(contact3));
  
  // clean up the list:
  VERIFY(TRUE, delete_contact(contact1));
  VERIFY(TRUE, delete_contact(contact2));
  VERIFY(TRUE, delete_contact(contact3));
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());
}

void test_bounds() {
  int contact;

  printf("\n*** Testing boundary values:\n");
  
  // 50 and 20 chars:
  VERIFY_NON_NEGATIVE(contact = new_contact("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbbbbbbb"));
  VERIFY(TRUE, add_phone(contact, 204, 5555555, "cccccccccccccccccccc"));

  VERIFY(TRUE, add_phone(contact, 100, 1000000, ""));
  VERIFY(FALSE, add_phone(contact, 99, 1000000, ""));
  VERIFY(FALSE, add_phone(contact, 100, 999999, ""));

  VERIFY(TRUE, delete_contact(contact));
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());
}

void test_invalid() {
  int contact;

  printf("\n*** Testing invalid parameters:\n");
  
  VERIFY(-1, new_contact("", ""));
  VERIFY(-1, new_contact("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", ""));
  VERIFY(-1, new_contact("a", "aaaaaaaaaaaaaaaaaaaaa"));
  
  // one good contact:
  VERIFY_NON_NEGATIVE(contact = new_contact("a", "b"));
  VERIFY(FALSE, add_phone(contact, -1, 5555555, ""));
  VERIFY(FALSE, add_phone(contact, 204, -1, ""));
  VERIFY(FALSE, add_phone(contact, 204, 5555555, "bbbbbbbbbbbbbbbbbbbbbbb"));

  VERIFY(FALSE, delete_contact(-1));
  VERIFY(FALSE, add_phone(-1, 204, 5555555, ""));

  VERIFY(-1, count_contact_numbers(0));
  VERIFY(-1, count_contact_numbers(-1));

  VERIFY(FALSE, remove_phone(-1, ""));

  // remove the one good contact:
  VERIFY(TRUE, delete_contact(contact));
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());

  // no longer valid:
  VERIFY(FALSE, add_phone(contact, 204, 5555555, ""));
  VERIFY(-1, count_contact_numbers(contact));
  
  // this should cause fopen() to fail on all systems:
  VERIFY(FALSE, save_contacts("."));
}

// Most tests are as simple as possible. This one is more complex because
// filling the capacity one item at a time would take a lot of code...
void test_capacity() {
  const int CONTACT_CAP = 100;
  const int PHONE_CAP = 500;
  int contact_ids[CONTACT_CAP];
  char name[3] = "aa";
  int count_successful_contacts, count_successful_phones, count;

  printf("\n*** Testing list capacity:\n");

  // this test only makes sense if the list starts out empty (which it should)
  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());

  // we're not going to VERIFY every single contact/phone (too much output,
  // and they're not each a separate test), just the final results

  count_successful_contacts = 0;
  for (int i = 0; i < CONTACT_CAP; i++) {
    name[0] = (i / 10) + 'a';
    name[1] = (i % 10) + 'a';
    contact_ids[i] = new_contact(name, "");
    if (contact_ids[i] > 0) {
      count_successful_contacts++;
    }
  }
  VERIFY(CONTACT_CAP, count_successful_contacts);

  count_successful_phones = 0;
  for (int i = 0; i < PHONE_CAP; i++) {
    if (add_phone(contact_ids[i % CONTACT_CAP], 204, 5555555, "mobile")) {
      count_successful_phones++;
    }
  }
  VERIFY(PHONE_CAP, count_successful_phones);

  VERIFY(CONTACT_CAP, count_contacts());
  VERIFY(PHONE_CAP, count_all_numbers());
  
  // can't exceed maximums:
  VERIFY(-1, new_contact("abc", ""));
  VERIFY(FALSE, add_phone(contact_ids[CONTACT_CAP - 1], 204, 5555555, "mobile"));

  // try again, adding all phone numbers to one contact
  
  count_successful_contacts = 1;
  count_successful_phones = count_contact_numbers(contact_ids[0]);
  for (int i = 1; i < CONTACT_CAP; i++) {
    count = count_contact_numbers(contact_ids[i]);
    if (remove_phone(contact_ids[i], "mobile")) {
      count_successful_contacts++;
    }
    for (int j = 0; j < count; j++) {
      if (add_phone(contact_ids[0], 204, 5555555, "mobile")) {
        count_successful_phones++;
      }
    }
  }
  VERIFY(CONTACT_CAP, count_successful_contacts);
  VERIFY(PHONE_CAP, count_successful_phones);
  VERIFY(PHONE_CAP, count_contact_numbers(contact_ids[0]));
  
  VERIFY(CONTACT_CAP, count_contacts());
  VERIFY(PHONE_CAP, count_all_numbers());
  
  // can't exceed maximums:
  VERIFY(-1, new_contact("abc", ""));
  VERIFY(FALSE, add_phone(contact_ids[0], 204, 5555555, "mobile"));
  
  // clean up the list:
  count_successful_contacts = 0;
  for (int i = 0; i < CONTACT_CAP; i++) {
    if (delete_contact(contact_ids[i])) {
      count_successful_contacts++;
    }
  }
  VERIFY(CONTACT_CAP, count_successful_contacts);

  VERIFY(0, count_contacts());
  VERIFY(0, count_all_numbers());
}

int main_tests() {
  printf("*** Starting tests...\n");

  test_empty_list();
  test_simple_list();
  test_bounds();
  test_invalid();
  test_capacity();
  
  if (0 == Tests_Failed) {
    printf("\nAll %d tests passed.\n", Tests_Passed);
  } else {
    printf("\nFAILED %d of %d tests.\n", Tests_Failed, Tests_Failed+Tests_Passed);
  }

  printf("\n*** Tests complete.\n");
  return 0;
}