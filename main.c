#include "pengap.h"

int main(int argc, char** argv) {

  pengap_init(&argc, &argv);

  // Everything you need customized, you
  // can do here.
  pengap_default_size(800, 600);

  pengap_load("http://www.google.com");

  return pengap_main();
}