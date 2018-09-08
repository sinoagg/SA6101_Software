#include <userint.h>
#include "Table.h"
#include "LoadPanel.h"
#include "TablePanel.h"
#include "Protocol.h" 

Table_TypeDef Table_ATTR;
//char ABC[11][20] ={"A","B","C","D","E","F","G","H","I","J","K", "L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"};

void Table(char table_title[][20], int column,int  columnWidth,int row) //��ʼ����������    
{			
		   
	                               
			InsertTableColumns(hTablePanel,TABLE_DISTABLE,1,column,VAL_USE_MASTER_CELL_TYPE);                     //����в�������� 
			InsertTableRows (hTablePanel,TABLE_DISTABLE ,-1 , row, VAL_USE_MASTER_CELL_TYPE);				      //����row�� 
			switch(TestPara.testMode)
			{
				case SWEEP_GATE_VOL: 
				case SWEEP_DRAIN_VOL:
				case NO_SWEEP_IT:
				case NO_SWEEP_RT:
				case ID_T:
					for(int j=1;j<=column;j++)
					{	
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //��������
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //�����п�
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+2)%3]); //�б��
					}
					break;
				case SWEEP_IV:
					for(int j=1;j<=column;j++)
					{
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_USE_LABEL_TEXT,1);                   //��������
						SetTableColumnAttribute(hTablePanel,TABLE_DISTABLE,j,ATTR_COLUMN_WIDTH,columnWidth); 		   //�����п�
						SetTableColumnAttribute(hTablePanel, TABLE_DISTABLE,j, ATTR_LABEL_TEXT, table_title[(j+1)%2]); //�б��
					}
					break;
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




