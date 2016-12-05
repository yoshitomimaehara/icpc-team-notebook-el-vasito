char red(char c){return c-'a';} //change if not only lowercase
struct vertex {
	int next[ALPHABET_SIZE],go[ALPHABET_SIZE],p,link;
	char pch;
	vector<int> leaf;
};
vertex t[NMAX];
int sz;
void aho_init(){ //do not forget!!
	t[0].p=t[0].link=-1;
	memset(t[0].next,-1,sizeof(t[0].next));
	memset(t[0].go,-1,sizeof(t[0].go));
	sz=1;
}
void add_string(char *s, int id){
	int v=0;
	for(int i=0;s[i];++i){
		char c=red(s[i]);
		if(t[v].next[c]<0){
			memset(t[sz].next,-1,sizeof(t[sz].next));
			memset(t[sz].go,-1,sizeof(t[sz].go));
			t[sz].p=v;t[sz].pch=c;t[sz].link=-1;
			t[v].next[c]=sz++;
		}
		v=t[v].next[c];
	}
	t[v].leaf.pb(id);
}
int go(int v, char c);
int get_link(int v){
	if(t[v].link<0)
		if(!v||!t[v].p)t[v].link=0;
		else t[v].link=go(get_link(t[v].p),t[v].pch);
	return t[v].link;
}
int go(int v, char c){//remember red
	if(t[v].go[c]<0)
		if(t[v].next[c]>=0)t[v].go[c]=t[v].next[c];
		else t[v].go[c]=v==0?0:go(get_link(v),c);
	return t[v].go[c];
}
