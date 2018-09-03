
/*
 * @author: rohith
 *
 * Dont use strncmp() for integers because it stops comparision if it encounters a null character.
 */

int FindRec(int relNum, Rid startRid, Rid *foundRid, char **recPtr, char *attrType, int attrSize, int attrOffset, char *valuePtr, int compOp)
{
	unsigned int slotmap, temp;
	char *recData;
	int retVal;
	if(relNum<0 || relNum>=MAXOPEN){
		//error
		return NOTOK;
	}

	if(catcache[relNum].occupied == false){
		//error
		return NOTOK;
	}

	if(startRid.pid >= catcache[relNum].numPgs){
		//error
		return NOTOK;
	}

	while(getNextValidRid(relNum,startRid, foundRid)==OK){
		ReadPage(foundRid->pid);

		slotmap = buffer[relNum].slotmap;
		temp = 1;
		temp = temp << (sizeof(int) - foundRid->slotnum - 1);
		if((slotmap & temp) != 0){ //slot is not empty -> record is valid
			recData = buffer[relNum].contents + RECORDSIZE*(foundRid->slotnum); //To be changed here after removing restriction
			*recPtr = recData;
			
			if(attrType[0]=='s'){ //string
				retVal=strncmp(recData+attrOffset, valuePtr, attrSize);
				switch(compOp){
					case EQ:{
						if(retVal == 0)
							return OK;
						break;
					}
					case GE:{
						if(retVal >= 0)
							return OK;
						break;
					}
					case GT:{
						if (retVal > 0)
							return OK;
						break;
					}
					case LE:{
						if (retVal <= 0)
							return OK;
						break;
					}
					case LT:{
						if(retVal < 0)
							return OK;
						break;
					}
					case NE: {
						if(retVal != 0)
							return 0K;
						break;
					}
				}
			}
			else if(attrType[0] == 'i'){ //int
				int value1 = *(int *)(recData+attrOffset);
				int value2 = *(int *)valuePtr;
				switch(compOp){
					case EQ:{
						if(value1 == value2)
							return OK;
						break;
					}
					case GE:{
						if(value1 >= value2)
							return OK;
						break;
					}
					case GT:{
						if (value1 > value2)
							return OK;
						break;
					}
					case LE:{
						if (value1 <= value2)
							return OK;
						break;
					}
					case LT:{
						if(value1 < value2)
							return OK;
						break;
					}
					case NE: {
						if(value1 != value2)
							return 0K;
						break;
					}
				}
			}
			else{ //unknown type
				  // Currently we dont support floats.
				return NOTOK;
			}
		}

		startRid = *foundRid;
	}
	return NOTOK;
}

