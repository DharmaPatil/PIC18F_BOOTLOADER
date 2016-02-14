/**********************************************************************
	�����ɉ�����ANK������␳.
 **********************************************************************
 */
#include "easy.h"
#include <malloc.h>
#include <string.h>

Usage(
	" ===== MPLINK .LST format converter =====\n"
	"Usage:\n"
	"$ mpfix infile outfile\n"
);

#define CRLF "\r\n"

static	char	infile[256];
static	char	outfile[256];

static	char 	curfile[256];

static	int		start_adr=0;
static	int		end_adr=0;

static	int		adr_u = 0;		// hexrec mode 4
static	unsigned char	maxlength=0;

/**********************************************************************
 *		����(c)��SJIS�����̂P�����ڊY������Ȃ�1
 **********************************************************************
 */
static	int	iskanji1(int c)
{
	c &= 0xff;
	if( (c >= 0x81) && (c < 0xa0) ) return 1;
	if( (c >= 0xe0) && (c < 0xfc) ) return 1;
	return 0;
}

/**********************************************************************
 *		������(s)��(n)�����ڂ�SJIS�����̂P�����ڊY������Ȃ�1
							  SJIS�����̂Q�����ڊY������Ȃ�2
 ����ȊO�Ȃ�0
 **********************************************************************
 */
static	int	iskanji_str(char *s,int n)
{
	int i,c,f=0;
	i=0;
	while(*s) {
		c = *s;
		if(f == 1) {
			f=2;				//SJIS�����Q������
		}else{
			if(iskanji1(c)) f=1;	//SJIS�����P������
			else f=0;				//ASCII
		}
		if(i>=n) return f;
		i++;
		s++;
	}
	return 0;
}

/**********************************************************************
 *		������ *s �Ɋ܂܂�镶��c�̈ʒu���E�[����T�[�`����.
 **********************************************************************
 *	�}�b�`���Ȃ��ꍇ�� (-1)��Ԃ�.
 *  �}�b�`�����ꍇ�́A���[����̕���(c)�̈ʒu�i�������j��Ԃ�.
 */
static int rindex(char *s,int c)
{
	int n = strlen(s);
	int i;
	for(i=n-1;i>=0;i--) {
		if(s[i]==c) return i;
	}
	return -1;
}

/**********************************************************************
 *		������ *s �̉E�[�ɂ���󔒕�����S�č폜����.
 **********************************************************************
 */
void chop_sp(char *s)
{
	int n = strlen(s);
	int i;
	int c = ' ';
	for(i=n-1;i>=0;i--) {
		if(	s[i] != c) {
			s[i+1]=0;
			return;
		}
	}
	
}

/**********************************************************************
 *		������ *s �𕶎���maxlength �ŃJ�b�g����.
 **********************************************************************
 */
void cut_string(char *s,int maxlength)
{
	if( iskanji_str(s,maxlength)==1 ) {
		s[maxlength]=0;
	}else{
		s[maxlength+1]=0;
	}
}
/**********************************************************************
 *		�啶���A���t�@�x�b�g�Ȃ�1��Ԃ�.
 **********************************************************************
 */
static	int	isALPHA(int c)
{
	if((c>='A')&&(c<='Z'))return 1;
	return 0;
}
/**********************************************************************
 *		.lst�t�@�C�����P�s�P�ʂŏ�������.
 **********************************************************************
 */
int	read_line(char *s)
{
	int n = strlen(s);
	int m = rindex(s,' ');
	char *t;
	if(m>=0) {
		t = s+m+1;
		if(isALPHA(t[0]) && (t[1]==':')) {
			s[m]=0;
			if(	strcmp(curfile,t)!=0) {
				strcpy(curfile,t);
				fprintf(ofp,"FILE:%s" CRLF,curfile);
			}
		}
	}
	
	chop_sp(s);
	if(	maxlength>=32 ) {
		cut_string(s,maxlength);
	}
	chop_sp(s);
	fprintf(ofp,"%s" CRLF,s);
}

/**********************************************************************
 *		.lst�t�@�C����ǂݍ���ŏ���.
 **********************************************************************
 */
void read_lst(void)
{
	char buf[4096];
	int rc,c;
	Ropen(infile);
	Wopen(outfile);
	while(1) {
		c = getc(ifp);if(c==EOF) break;

		if(c>=0x80) {
			printf("BAD CODE:%x\n",c);
			if(c==0xae) {
				fprintf(ofp,"(TM)");
			}else{
				fprintf(ofp,"'");
			}
		}else{
			putc(c,ofp);
		}
	}
	Wclose();
	Rclose();

}

/**********************************************************************
 *		���C������
 **********************************************************************
 */
int	main(int argc,char **argv)
{
	int m=80;
	Getopt(argc,argv);
	if(argc<3) {
		usage();
	}
	strcpy(infile,argv[1]);
	strcpy(outfile,argv[2]);
	read_lst();

	return 0;
}

/**********************************************************************
 *		
 **********************************************************************
 */
