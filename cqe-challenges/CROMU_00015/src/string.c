/*

Author: John Berry <hj@cromulence.co>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "string.h"

/**
 * Frees a string and its buffer. The calling function does not need to free the structure
 * @param str Pointer to a string structure
 * @return Returns nothing
 **/ 
void freeString( pstring str )
{
	if ( str == NULL ) {
		return;
	}

	/// If buffer is not NULL then free it. The length should be maxlength
	if ( str->buffer ) {
		deallocate( str->buffer, str->maxlength );
	}

	deallocate(str, sizeof(string));

	return;
}

/**
 * Skips any characters associated with a url:
 *	alphanumeric, '.', '/', and ':'
 * @param str Pointer to the string structure
 * @return Returns the final cgc_index after the URL or -1 on failure
 **/
int skipUrl( pstring str )
{
	int retval = -1;
	int cgc_index = 0;
	char c = '\x00';

	if ( str == NULL ) {
		goto end;
	}

	/// Save the starting cgc_index
	cgc_index = str->cgc_index;

	/// Loop until the end of the buffer or an invalid character is encountered
	while ( cgc_index < str->maxlength ) {
		c = str->buffer[cgc_index];

		if ( !isalnum(c) && c != '.' && c != '/' && c != ':' ) {
			/// Set the new cgc_index past to the invalid character
			str->cgc_index = cgc_index;

			/// Set the return value to the new cgc_index
			retval = cgc_index;
			break;
		}

		cgc_index++;
	}

end:
	return retval;
}

/**
 * Returns the current cgc_index
 * @param str Pointer to the string structure
 * @param outIndex Pointer to an integer to store the value
 * @return Returns the current cgc_index into the string
 **/
int getIndex( pstring str, int *outIndex )
{
	if ( str == NULL ) {
		return -1;
	}

	*outIndex = str->cgc_index;

	return str->cgc_index;
}

/**
 * Skip digits, '+' or '-'
 * @param str Pointer to the string structure
 * @return The final cgc_index after any integer data or -1 on error
 **/
int skipInt( pstring str ) 
{
	int retval = -1;
	int cgc_index = 0;
	char c = '\x00';

	if ( str == NULL ) {
		return -1;
	}

	cgc_index = str->cgc_index;

	while( cgc_index < str->maxlength ) {
		c = str->buffer[cgc_index];

		if ( c == '+' || c == '-' || isdigit(c) ) {
			cgc_index++;
			continue;
		} else {
			str->cgc_index = cgc_index;
			retval = str->cgc_index;
			break;
		}
	}

	return retval;
}

/**
 * Skip digits, '+', '-', or '.'
 * @param str Pointer to the string structure
 * @return The final cgc_index after any float data or -1 on error
 **/
int skipFloat( pstring str ) 
{
	int retval = -1;
	int cgc_index = 0;
	char c = '\x00';

	if ( str == NULL ) {
		return -1;
	}

	cgc_index = str->cgc_index;

	while( cgc_index < str->maxlength ) {
		c = str->buffer[cgc_index];

		if ( c == '.' || c == '+' || c == '-' || isdigit(c) ) {
			cgc_index++;
		} else {
			str->cgc_index = cgc_index;
			retval = str->cgc_index;
			break;
		}
	}

	return retval;
}

/**
 * Copy a segment of the string out
 * @param str Pointer to the string structure
 * @param start Start cgc_index for the copy
 * @param end End cgc_index for the copy
 * @return Returns a pointer to the requested data or NULL on failure.
 *	This buffer needs to be freed by the caller.
 **/
char *copyData( pstring str, int start, int end )
{
	char *data = NULL;
	int length = 0;

	if ( str == NULL ) {
		return data;
	}

	/// The start and end must be greater than 0
	if ( end < 0 || start < 0) {
		return NULL;
	}

	/// If they are equal then there is nothing to copy
	if ( end == start ) {
		return NULL;
	}

	/// End must be after start
	if ( end < start ) {
		return data;
	}

	/// Both must be within the valid range
	if ( str->maxlength < end || str->maxlength < start) {
		return data;
	}

	/// Calculate string length
	length = end - start;

	if ( allocate( length+1, 0, (void**)&data) != 0 ) {
		data = NULL;
		return data;
	}

	bzero( data, length + 1 );

	cgc_memcpy( data, str->buffer + start, length );

	return data;
}

/**
 * Skip to non-alpha characters
 * @param str Pointer to the string structure
 * @param Returns the final cgc_index or -1 on failure
 **/
int skipAlpha( pstring str )
{
	int retval = -1;
	int cgc_index = 0;

	if ( str == NULL ) {
		return retval;
	}

	cgc_index = str->cgc_index;

	while ( cgc_index < str->maxlength ) {
		if ( !isalpha( str->buffer[cgc_index] ) ) {
			str->cgc_index = cgc_index;
			retval = str->cgc_index;
			return retval;
		}

		cgc_index++;
	}

	return retval;
}

/**
 * Skip to non alphanumeric or spacecharacters
 * @param str Pointer to the string structure
 * @param Returns the final cgc_index or -1 on failure
 **/
int skipToNonAlphaNumSpace( pstring str )
{
	int retval = -1;
	int cgc_index = 0;

	if ( str == NULL ) {
		return retval;
	}

	cgc_index = str->cgc_index;
	while ( cgc_index < str->maxlength ) {
		if ( !isalnum( str->buffer[cgc_index] ) && str->buffer[cgc_index] != ' ') {
			str->cgc_index = cgc_index;
			retval = str->cgc_index;
			return retval;
		}

		cgc_index++;
	}

	return retval;
}

/**
 * Skip to non alphanumeric characters
 * @param str Pointer to the string structure
 * @param Returns the final cgc_index or -1 on failure
 **/
int skipToNonAlphaNum( pstring str )
{
	int retval = -1;
	int cgc_index = 0;

	if ( str == NULL ) {
		return retval;
	}

	cgc_index = str->cgc_index;
	while ( cgc_index < str->maxlength ) {
		if ( !isalnum( str->buffer[cgc_index] ) ) {
			str->cgc_index = cgc_index;
			retval = str->cgc_index;
			return retval;
		}

		cgc_index++;
	}

	return retval;
}

/**
 * Increment the string by a one 
 * @param str Pointer to the string structure
 * @return Returns the cgc_index skipped to or -1 on failure
 **/
int incChar( pstring str )
{
	int retval = -1;

	if ( str == NULL ) {
		goto end;
	}

	if ( str->cgc_index + 1 < str->maxlength ) {
		str->cgc_index += 1;
		retval = str->cgc_index;
	}


end:
	return retval;
}

/**
 * Increment the string by a certain length
 * @param str Pointer to the string structure
 * @param count Amount by which to increase the cgc_index
 * @return Returns the cgc_index skipped to or -1 on failure
 **/
int skipLength( pstring str, int count )
{
	int retval = -1;

	if ( str == NULL ) {
		goto end;
	}

	if ( str->cgc_index + count < str->maxlength ) {
		str->cgc_index += count;
		retval = str->cgc_index;
	}


end:
	return retval;
}

/**
 * Check if the next character to be parsed is the same as the argument
 * @param str Pointer to the string structure
 * @param c Character to test for
 * @return Returns 1 if true, 0 if false
 **/
int atChar( pstring str, char c )
{
	if ( str == NULL ) {
		return 0;
	}

	if ( str->buffer[ str->cgc_index ] == c ) {
		return 1;
	}

	return 0;
}

/**
 * Skip to the next character as specified by the argument
 * @param str Pointer to the string structure
 * @param c Character to locate
 * @return Returns the cgc_index of the next instance or -1 on failure
 **/
int skipTo( pstring str, char c )
{
	int cgc_index = 0;
	int retval = -1;

	if ( str == NULL ) {
		goto end;
	}

	cgc_index = str->cgc_index;

	while ( cgc_index < str->maxlength ) {
		if ( str->buffer[cgc_index] == c ) {
			str->cgc_index = cgc_index;
			retval = cgc_index;
			goto end;
		}

		cgc_index++;
	}

end:
	return retval;
}

/**
 * Initialize a new string with an existing buffer
 * @param data Pointer to the data this structure will manage
 * @return Returns a pointer to a string structure or NULL on failure
 **/
pstring initString( char *data )
{
	pstring newString = NULL;
	int length = 0;

	if (data == NULL ) {
		goto end;
	}	

	length = cgc_strlen(data)+1;

	if ( allocate( sizeof(string), 0, (void**)&newString) != 0 ) {
		newString = NULL;
		goto end;
	}

	if ( allocate( length, 0, (void**)&(newString->buffer)) != 0 ) {
		deallocate( newString, sizeof(string) );
		newString = NULL;
	}

	bzero( newString->buffer, length );
	cgc_memcpy( newString->buffer, data, length-1 );

	newString->maxlength = length;
	newString->cgc_index = 0;

end:
	return newString;
}

/**
 * Skip any whitespace at the start of the buffer
 * @param st String structure containing the data to skip
 * @return Returns the new cgc_index
 **/
int skipWhiteSpace( pstring st )
{
        int retval = -1;
        int si = 0;

	char c = '\x00';

        if ( st == NULL ) {
                goto end;
        }

	if ( st->maxlength <= st->cgc_index ) {
		return -1;
	}

        si = st->cgc_index;

        while ( si < st->maxlength && (st->buffer[ si ] == '\n' || st->buffer[si] == '\t' || st->buffer[si] == ' ' || st->buffer[si] == '\r') ) {
                si++;
        }

        retval = si;
        st->cgc_index = si;

end:
        return retval;
}
