#include <userint.h>
#include "Table.h"
#include "LoadPanel.h"
#include "TablePanel.h"

Table_TypeDef Table_ATTR;

char ABC[11][20] ={"A","B","C","D","E","F","G","H","I","J","K"};

//char Table_title_IV[11][20] ={"Current(A)","Voltage(V)","Current(A)","Voltage(V)"};
//char Table_title_VI[11][20] ={"Current(A)","Voltage(V)","Current(A)","Voltage(V)"}; 
//char Table_title_IT[11][20] ={"Current(A)","Time(S)","Current(A)","Time(S)"};
 //int column=4;        //����
 //int column_width=290;//�п�



   void Table_init(char table_title[][20], int column, columnWidth) //��ʼ����������    
{			
		   
			InsertTableColumns(hTablePanel,TABLE_DISTABLE,1,column,VAL_CELL_STRING);              //����в�������� 
			InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1 , 1, VAL_CELL_STRING);				      		  //����1�� 
			for(int i=1;i<column+1;i++) {
			SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,i,ATTR_USE_LABEL_TEXT,1);                     //��������
			SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,i,ATTR_COLUMN_WIDTH,columnWidth); 			  //�����п�
			SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE, i, ATTR_LABEL_TEXT, ABC[i-1]);              //�б��
		    SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (i, 1), table_title[i-1]);	          //�ֱ����ñ��� 

			
			}
			
}
//�������
int CVICALLBACK AddTitleCallback (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	/*switch (event)											  
	{
		case EVENT_LEFT_CLICK_UP:
			Table_init(Table_title_IT,column, column_width );
			SetCtrlAttribute (hTablePanel, TABLE_ADDROW, ATTR_DIMMED,0);       
			SetCtrlAttribute (hTablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,1); 				
			break;
	}*/
	return 0;
}

//�������
int CVICALLBACK AddRowCallback (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{   	switch (event)
	{			   
			case EVENT_LEFT_CLICK_UP:
				/*int row;
   	            InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1, 1, VAL_CELL_NUMERIC);				          //����1�� 
				GetNumTableRows (hTablePanel, TABLE_DISTABLE, &row); 										  //�õ���ǰ����
				for(int i=1;i<=column;i++){
					//��ӱ������
					 SetTableCellVal (hTablePanel, TABLE_DISTABLE, MakePoint (i,row ), i*100.0);//��i��     
					//���ݾ�����ʾЧ��   
					 SetTableCellAttribute (hTablePanel, TABLE_DISTABLE, MakePoint (i,row ), ATTR_CELL_JUSTIFY, VAL_CENTER_CENTER_JUSTIFIED); 
				}
					int MaxRow; //����tanle�߶Ⱥ���ʾ������ʾ���һ������ 
					GetNumTableRows(hTablePanel,TABLE_DISTABLE,&MaxRow);
					SetCtrlAttribute(hTablePanel,TABLE_DISTABLE,ATTR_FIRST_VISIBLE_ROW,MaxRow);*/
							
				break;
	}
	return 0;
}
//ɾ������
int CVICALLBACK DeleteCalback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_LEFT_CLICK_UP:
			DeleteTableRows (hTablePanel, TABLE_DISTABLE, 1, -1);
	 		DeleteTableColumns (hTablePanel, TABLE_DISTABLE, 1, -1);	
		    SetCtrlAttribute (hTablePanel, TABLE_ADDROW, ATTR_DIMMED,1);       
		    SetCtrlAttribute (hTablePanel, TABLE_ADDTITLE,  ATTR_DIMMED,0);
	 	 
		break;	
	}
	return 0;
}
 //������ӱ���ɫ
int CVICALLBACK ColorCallback (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{		 
	   switch(event){
		case EVENT_LEFT_CLICK_UP:
			int val;
			GetCtrlVal(hTablePanel,TABLE_ADDBGCOLOR,&val); //���checkbox��ֵ
			 int rowIndex;
             int numRows;
			 GetNumTableRows (hTablePanel, TABLE_DISTABLE, &numRows);
			   for (rowIndex=1; rowIndex <= numRows; rowIndex++)
		        {
		         if((val) &&((rowIndex % 2) ==1))
					 SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, 0xD0D0D0L);//��ɫ      
		         else
		            SetTableCellRangeAttribute (hTablePanel, TABLE_DISTABLE,VAL_TABLE_ROW_RANGE(rowIndex),ATTR_TEXT_BGCOLOR, VAL_WHITE);//��ɫ   
		        }
		
	 	   break;
	    } 

	return 0;
}




