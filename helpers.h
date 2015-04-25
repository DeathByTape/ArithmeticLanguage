/**
 * helpers.h
 *
 * Lexing helpers. In summary, methods for building up objects.
 * This includes both strings and our final structure.
 *
 * Author: Dennis J. McWherter, Jr. <dennis@deathbytape.com>
 */

/** Parsed object helpers */
/** Enum representing parsed object type */
typedef enum {
  INT,
  STRING
} PARSE_TYPE;

/** Object representing the result of a computation (i.e. a string or exp) */
typedef struct {
  PARSE_TYPE type;
  void* value;
} parsed_obj_t;

/** Simple graph representing how objects are appended */
typedef struct {
  parsed_obj_t** links;
  int len;
  int cap;
} parsed_graph_t;

/**
 * Initialize the global parsed graph
 */
void pg_init();

/**
 * Destroy the global parsed graph
 */
void pg_destroy();

/**
 * Insert a string into the global parsed graph
 *
 * @param str String to insert (a copy will be made)
 */
void pg_insert_str(const char* str);

/**
 * Insert an integer into the global parsed graph
 *
 * @param val Integer to insert
 */
void pg_insert_int(int val);

/**
 * Print the current graph
 */
void pg_print_graph();

/** String helpers */
/**
 * Update a string by appending a new value
 *
 * @param c Character to append to string
 */
void str_update(char c);

/**
 * Append a full string to current global string
 *
 * @param str String to append
 */
void str_update_str(const char* str);

/**
 * Get a string and clear it internally.
 *
 * NOTE: You must copy the returned string if you do not want it to be
 *       overwritten.
 *
 * @return Pointer to the current string
 */
const char* str_get();

/**
 * Clear global string
 */
void str_clear();

/**
 * Free the internal string buffer
 */
void str_free();

