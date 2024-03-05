class mysql_wrapper
{
	void call_procedure_str()
	{
	    char req[21 + 16 + 1] = "CALL PROCEDURE DUSR(0x";
	    char* it = req + 21;
	    it = itoh(it, userid);
	    *it++ = ')';
	}
}