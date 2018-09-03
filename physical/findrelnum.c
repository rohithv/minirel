/*
 * @author : bhavani
 */

int FindRelNum(char * relName)
{
	int i;
	for(i=0;i<MAXOPEN;i++){
		if( catcache[i].occupied ==  true){
			if( strcmp(relName, catcache[i].relName) == 0){
				return i;
			}
		}
	}
	return NOTOK;	
}
