#include "includes/Dictionary/Dictionary.h"

using namespace std;

Dictionary &webContent = *(new Dictionary(3));
webContent("/index.html","<h1>\nnaaa\n</h1>");
webContent("/styles.css","")
;