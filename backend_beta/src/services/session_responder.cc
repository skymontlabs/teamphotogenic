#include <cassandra.h>

// Macro to extract and convert a column value from a CassRow by index.
// Assumes that 'row' is a valid pointer to a CassRow and 'index' is the column index.
// 'type' is the Cassandra type to extract, and 'var' is the variable to store the extracted value.

#define EXTRACT_COLUMN_VALUE_BY_INDEX(row, index, type, var) \
  do { \
    const CassValue* value = cass_row_get_column((row), (index)); \
    if (value != NULL && !cass_value_is_null(value)) { \
      if (cass_value_get_##type(value, &(var)) != CASS_OK) { \
        fprintf(stderr, "Error extracting column value at index %d\n", (index)); \
      } \
    } else { \
      fprintf(stderr, "Null or invalid value for column at index %d\n", (index)); \
    } \
  } while (0)


#define EXTRACT_COLUMN_VALUE_BY_INDEX_TO_ARRAY(row, index, type, array_ptr) \
  do { \
    const CassValue* value = cass_row_get_column((row), (index)); \
    if (value != NULL && !cass_value_is_null(value)) { \
      if (cass_value_get_##type(value, (array_ptr)) != CASS_OK) { \
        fprintf(stderr, "Error extracting column value at index %d into array\n", (index)); \
      } \
    } else { \
      fprintf(stderr, "Null or invalid value for column at index %d\n", (index)); \
    } \
  } while (0)

// Macro to extract an int32 value from a CassRow by index into an int32 array.
#define EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, index, array_ptr) \
  EXTRACT_COLUMN_VALUE_BY_INDEX_TO_ARRAY(row, index, int8, array_ptr)

// Macro to extract an int32 value from a CassRow by index into an int32 array.
#define EXTRACT_COLUMN_VALUE_BY_INDEX_INT16(row, index, array_ptr) \
  EXTRACT_COLUMN_VALUE_BY_INDEX_TO_ARRAY(row, index, int16, array_ptr)

// Macro to extract an int32 value from a CassRow by index into an int32 array.
#define EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, index, array_ptr) \
  EXTRACT_COLUMN_VALUE_BY_INDEX_TO_ARRAY(row, index, int32, array_ptr)

// Macro to extract an int64 value from a CassRow by index into an int64 array.
#define EXTRACT_COLUMN_VALUE_BY_INDEX_INT64(row, index, array_ptr) \
  EXTRACT_COLUMN_VALUE_BY_INDEX_TO_ARRAY(row, index, int64, array_ptr)

#define EXTRACT_COLUMN_VALUE_BY_INDEX_STRING(row, index, str, str_length) \
  do { \
    const CassValue* value = cass_row_get_column((row), (index)); \
    if (value != NULL && !cass_value_is_null(value)) { \
      if (cass_value_get_string(value, &str, &str_length) != CASS_OK) { \
        fprintf(stderr, "Error extracting string at index %d\n", (index)); \
      } \
    } else { \
      fprintf(stderr, "Null or invalid value for string column at index %d\n", (index)); \
    } \
  } while (0)

#define EXTRACT_COLUMN_VALUE_BY_INDEX_BLOB(row, index, var) \
  do { \
    const CassValue* value = cass_row_get_column((row), (index)); \
    if (value != NULL && !cass_value_is_null(value)) { \
      CassBytes temp; \
      if (cass_value_get_bytes(value, &temp) != CASS_OK) { \
        fprintf(stderr, "Error extracting blob at index %d\n", (index)); \
      } else { \
        var = temp; /* Assign to your CassBytes variable */ \
      } \
    } else { \
      fprintf(stderr, "Null or invalid value for blob column at index %d\n", (index)); \
    } \
  } while (0)


void on_result(CassFuture* future, void* data) {
  /* This result will now return immediately */
  CassError rc = cass_future_error_code(future);
  printf("%s\n", cass_error_desc(rc));
}




void read_list_cbk(CassFuture* future, void* data)
{
	db_cbk_data* d = (db_cbk_data*)data;
  	CassError rc = cass_future_error_code(future);

  	uint8_t* buf = pal->alloc();
  	uint8_t* ptr = buf;
  	gateway* gwy = d->gwy;

 	if (rc == CASS_OK) {
		const CassResult* result = cass_future_get_result(future);

		// result available
		if (result != NULL) {
			int rowct = cass_result_row_count(result);
			WRITE32(ptr, rowct)

			// Iterate over the results.
			for (int i = 0; i < rowct; i++) {
				// Get the current row.
				CassRow* row = cass_result_get_row(result, i);

				if (row) {
					// call function here
				}
			}

			cass_statement_free(statement);
			cass_result_free(result);
			//cass_session_free(session);

			gwy->send_response(buf/*to be sent*/, ptr - buf /*length*/, d/* info to be used, then to be deallocated */);
		} else {
			/* The error code and message will be set instead */
			CassError error_code = cass_future_error_code(future);
			CassString error_message = cass_future_error_message(future);
			/* Handle error */
	  		// return 404
		}

  	} else {
  		// return 404
  	}
}

// Since modifications are to be changed,
void insupd_cbk(CassFuture* future, void* data)
{
	// Check for errors
	if (cass_future_error_code(query_future) == CASS_OK) {
	  // The insert was successful
	} else {
	  // An error occurred
	  const char* message;
	  size_t message_length;
	  cass_future_error_message(query_future, &message, &message_length);
	  fprintf(stderr, "Insert error: '%.*s'\n", (int)message_length, message);
	}

	// Free the future when done
	cass_future_free(query_future);
}


// FROM HERE DOWN, DO NOT INCLUDE COPYABLE CODE, ONLY INVOLVE SERIALIZATIONS


// Get experiments from DB
void read_exps_cbk(CassFuture* future, void* data)
{
	// id of experiment
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT64(row, 0, img0);
	ptr += 8;

	// 4 images (4 IDs [64 bit])
	EXTRACT_COLUMN_VALUE_BY_INDEX(row, 1, int64, img0);
	ptr += 8;
	EXTRACT_COLUMN_VALUE_BY_INDEX(row, 2, int64, img0);
	ptr += 8;
	EXTRACT_COLUMN_VALUE_BY_INDEX(row, 3, int64, img0);
	ptr += 8;
	EXTRACT_COLUMN_VALUE_BY_INDEX(row, 4, int64, img0);
	ptr += 8;
	
	// Title (pascal string)
	EXTRACT_COLUMN_VALUE_BY_INDEX_STRING(row, 5, title, title_length);
	WRITE32(ptr, title_length)
	memcpy(ptr, title, title_length);
	ptr += title_length;

	// Images (32 bit)
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, 6, ptr);
	ptr += 4;
	
	// Votes (32 bit)
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, 7, votes);
	ptr += 8;

	// Date created
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT64(row, 8, created);
	ptr += 4;
	
	// Comments
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, 9, comments);
	ptr += 4;
}


// Get experiment ID (metadata only)
uint8_t* read_exp_meta_cbk(uint8_t* ptr, CassRow* row)
{
	// same as read_exp_list_cbk
}

// Get experiment ID (images only)
uint8_t* read_exp_images_cbk(uint8_t* ptr, CassRow* row)
{
	// Likert score
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT64(row, 0, ptr);
	ptr += 8;
	
	// Elo score
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT64(row, 1, ptr);
	ptr += 8;
	
	// Votes (32 bit)
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, 2, ptr);
	ptr += 4;
	
	// Comments
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, 3, ptr);
	ptr += 4;

	return ptr;
}

// Read elo data from one image
uint8_t* read_elos_cbk(uint8_t* ptr, CassRow* row)
{
	// Loser
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, 0, ptr);
	++ptr;

	// Winner
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, 1, ptr);
	++ptr;

	return ptr;
}

// Read likert data from one image
uint8_t* read_likerts_cbk(uint8_t* ptr, CassRow* row)
{
	// Rating
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, 0, ptr);
	++ptr;

	// Tag
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT32(row, 1, int32, ptr);
	ptr += 4;

	// Comment
	EXTRACT_COLUMN_VALUE_BY_INDEX_STRING(row, 2, title, title_length);
	++ptr;
	WRITE32(ptr, title_length)
	memcpy(ptr, title, title_length);
	ptr += title_length;

	return ptr;
}

// Read user
uint8_t* read_user_cbk(uint8_t* ptr, CassRow* row)
{
	// Email
	EXTRACT_COLUMN_VALUE_BY_INDEX_STRING(row, 0, title, title_length);
	++ptr;
	WRITE32(ptr, title_length)
	memcpy(ptr, title, title_length);
	ptr += title_length;

	// Phone

	// Gender
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, 2, ptr);
	++ptr;

	// Age
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, 3, ptr);
	++ptr;

	// Habits
	EXTRACT_COLUMN_VALUE_BY_INDEX_INT8(row, 4, ptr);
	++ptr;

	// Preferences

	// Alerts

	return ptr;
}



// Callback after get experiment from DB
void* update_exp_cbk(CassFuture* future, void* data)
{
	db_cbk_data* d = (db_cbk_data*)data;
  	CassError rc = cass_future_error_code(future);

  	uint8_t* buf = pal->alloc();
  	gateway* gwy = d->gwy;

 	if (rc == CASS_OK) {
		const CassResult* result = cass_future_get_result(future);

		// result available
		if (result != NULL) {
			int rowct = cass_result_row_count(result);
		}
	}

	/*
	Get experiment 

	Title? (Optional if coming with knowledge)
	Num images (also optional)
	X images
	image id
	Votes
	Score
	Comments
	*/
}
