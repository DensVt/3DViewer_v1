#include "test.h"

START_TEST(test_count_ver_and_edges) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_1.txt", &data);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_scale_1) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_1.txt", &data);
  scale(1.1f, &data);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_moove_1) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_1.txt", &data);
  moove(&data, 1, 1);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_rot_x) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_1.txt", &data);
  rot_x(&data, 20);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_rot_y) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_1.txt", &data);
  rot_y(&data, 20);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_rot_z) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_1.txt", &data);
  rot_z(&data, 20);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_slash) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_2.txt", &data);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

START_TEST(test_minus) {
  main_data data = {NULL, 0, NULL, 0,   0,    0, 0, 0, 0,
                    0,    0, 0,    0.5, NULL, 0, 0, 1};
  parcer("tests/test_files/test_file_3.txt", &data);
  ck_assert_int_eq(data.count_edge, 12);
  ck_assert_int_eq(data.count_ver, 8);
  remove_data(&data);
}
END_TEST

void srunner_add_3dv(SRunner *sr) {
  Suite *suite = suite_create("test_backend");
  TCase *tcase_counter = tcase_create("test_parcer_counter");

  tcase_add_test(tcase_counter, test_count_ver_and_edges);
  tcase_add_test(tcase_counter, test_scale_1);
  tcase_add_test(tcase_counter, test_moove_1);
  tcase_add_test(tcase_counter, test_rot_x);
  tcase_add_test(tcase_counter, test_rot_y);
  tcase_add_test(tcase_counter, test_rot_z);
  tcase_add_test(tcase_counter, test_slash);
  tcase_add_test(tcase_counter, test_minus);

  suite_add_tcase(suite, tcase_counter);
  srunner_add_suite(sr, suite);
}

int main(void) {
  Suite *s = suite_create("parcer_tests");
  SRunner *sr = srunner_create(s);
  int nf;

  srunner_add_3dv(sr);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}