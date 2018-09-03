/*
 * @author : bhavani
 */


int OpenRel(char *relName)
{
	int relNum;
	
	//Check whether relation exists. else return NOTOK
	if( access(relName, F_OK) == -1){
		return NOTOK;
	}
	
	//check whether file exists in catalog cache if exists return relNum
	relNum =  FindRelNum(relName);
	if( relNum != NOTOK){
		return relNum; 
	}
	
	Rid startRid,foundRid;
	char *recPtr;
	
	startRid.pid=0;
	startRid.slotnum=1;
	
	if(FindRec(0,startRid,&foundRid,&recPtr,"s",15,0,relName,EQ)==NOTOK){
		//error
		return NOTOK;
	}
	
	for(i=2;i<MAXOPEN;i++){
		if(catcache[i].occupied==true){
			continue;
		}
		strncpy(catcache[i].relName, recPtr,15); 
		catcache[i].recLength= ReadIntFromBinary(recPtr+1*15);
		catcache[i].recsPerPg= 4;
		catcache[i].numAttrs= ReadIntFromBinary(recPtr+3*15);
		catcache[i].numRecs= ReadIntFromBinary(recPtr+4*15);
		catcache[i].numPgs= ReadIntFromBinary((recPtr+5*15);
		
		catcache[i].relcatRid.pid= foundRid.pid;
		catcache[i].relcatRid.slotnum= foundRid.slotnum;
		catcache[i].occupied= true;
		catcache[i].modified= false;
		catcache[i].relFile= fopen(relName,"rb+");
		
		catcache[i].attrList= createRelAttrCache(relName,catcache[i].numAttrs);
		break;
	}
	return OK;
}

/****return Relation attribute List Head(RelAttrHead)***
 Arguments : relation name, Number of attributes of relation
 */

Attrcat *createRelAttrcache(char *relName,int attrNum){
	
	AttrCat *RelAttrHead= NULL,*temp;
	int i;
	Rid startRid,foundRid;
	char *recPtr;
	
	//first 11 entries in the attribute catalog corresponds to relcat and attrcat
	startRid.pid= 2; 
	startRid.slotnum= 2;
	
	// create linked list of attributes in reverse order
	for(i=0;i<attrNum;i++){
		FindRec(1,startRid,&foundRid,&recPtr,"s",15,0,relName,EQ);
		
		temp= (Attrcat *)malloc(sizeof(Attrcat));
	
		strncpy(temp.relName, recPtr,15);
		strncpy(temp.attrName, recPtr+1*15,15);
		strcpy(temp.type, recPtr+2*15,15);
		temp.length= 15;
		temp.offset= ReadIntFromBinary(recPtr+4*15);
	
		temp->next= relcatAttrHead;
		RelAttrHead= temp;
		
		startRid= foundRid;
	}
	
	return RelAttrHead;
}
