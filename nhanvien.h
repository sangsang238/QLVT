#ifndef NHANVIEN_H_INCLUDED
#define NHANVIEN_H_INCLUDED
#include "cthoadon.h"
#include "ThanhTimKiem.h"
#include "nhap.h"
#include "function.h"
#include "editor.h"

#define SizeofCaptionNV 5
#define SizeofMANV 20
#define SizeofTENNV 20
#define SizeofHONV 20
#define SizeofPHAI 3
using namespace std;

NhanVien * FindNVBySoHD(DSNhanVien dsnv,string SoHD)
{
    for(int i=0;i<dsnv.Size;i++)
    {
        NodeHoaDon * hd = dsnv.DsNhanVien[i]->DSHoaDon;
        while(hd!=NULL)
        {
            if(SoHD==hd->Data.SoHD)
                return dsnv.DsNhanVien[i];
            hd = hd->Next;
        }
    }
    return NULL;
}

string captionNV[5] = {"Ma nhan vien :",
                       "Ho nhan vien :",
                       "Ten nhan vien :",
                       "Phai :",
					   "Luu : "};

void InNhanVien(int x,int y,NhanVien nv)
{
    Caption(captionNV,SizeofCaptionNV,x,y);
    gotoxy(x+20,y);
    cout<<nv.MANV;
    gotoxy(x+20,y+2);
    cout<<nv.HO;
    gotoxy(x+20,y+4);
    cout<<nv.TEN;
    gotoxy(x+20,y+6);
    cout<<nv.PHAI;
}



string KiemTraLoiNV(bool mode,NhanVien nv,DSNhanVien dsnv)
{
    string loi = "";
    if(nv.HO == ""||nv.TEN == ""||nv.MANV == "" ||nv.PHAI == "")
        loi += " Ban Nhap chua du du lieu,";
    if(nv.PHAI != "NAM" && nv.PHAI != "NU")
        loi += " Phai chi co the la (NAM/NU),";
    if(mode == 0 && SeachNV(dsnv,nv.MANV) != -1) // mode = 0 them nhan vien, mode != 0 sua nhan vien
        loi += " Ma nhan vien ban nhap bi trung,";
    return loi;

}

void LuuNhanVien(char &pn,int &lpn,bool &End,bool mode,NhanVien nv,DSNhanVien dsnv)
{
    if(pn==ENTER)
        {
            string Loi = KiemTraLoiNV(mode,nv,dsnv);
            if(Loi!="")
                ThongBaoGet(Loi,pn);
            else
                End = 1;

        }
}
void NhapNV(int x,int y,bool mode,char &pn,NhanVien &nhanvien,DSNhanVien &dsnv)
{
    InNhanVien(x,y,nhanvien);
    gotoxy(x+20,y);
    int chon = 0;
    pn = 17;
    int lpn = -1;
    bool End = 0;
    while(true)
    {
        if(pn == ESC)
            if(Thoat()==1){
            	ClearInsideBox(36, 39, 33, 159);// Xoa man hinh thong bao;
            	return;
			}
        if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionNV,x+20,y,End);
        else
        {
            pn = getch();
            if(pn == -32)
            {
                pn = getch();
                lpn = 1;
            }
            if(pn == ESC)
                if(Thoat()==1){
            	ClearInsideBox(36, 39, 33, 159);// Xoa man hinh thong bao;
            	return;
			}
            if(chon==SizeofCaptionNV-1) LuuNhanVien(pn,lpn,End,mode,nhanvien,dsnv);
            if(End==1)break;
            if(PhimNong(pn, 1)==1)
                XuLiPhimNong(chon,pn,SizeofCaptionNV,x+20,y,End);

        }
        if(End==1) break;
        switch(chon)
        {
            case 0 :if(mode==0){
                        NhapChuoi(nhanvien.MANV,x+20,y+chon*2,SizeofMANV,pn,lpn,3);break;
                    }else
                    {
                        gotoxy(x+20,y+chon*2);cout<<nhanvien.MANV;break;
                    }

            case 1 :NhapChuoi(nhanvien.HO,x+20,y+chon*2,SizeofTENNV,pn,lpn,5); break;
            case 2 :NhapChuoi(nhanvien.TEN,x+20,y+chon*2,SizeofTENNV,pn,lpn,2); break;
            case 3 :NhapChuoi(nhanvien.PHAI,x+20,y+chon*2,SizeofPHAI,pn,lpn,2); break;
            case 4 :LuuNhanVien(pn,lpn,End,mode,nhanvien,dsnv);

        }
    }
}
int ThemMoiNhanVien(DSNhanVien &dsnv)
{
    int x = 161 ; int y = 26;
    int p = 0;
    char pn;
    do
    {
        pn = 17;
        ClearInsideBox(23,39,166,199);//Xoa man hinh edit
        Caption(captionNV,SizeofCaptionNV,x,y);
        NhanVien nhanvien ;
        NhapNV(x,y,0,pn,nhanvien,dsnv);
        if(pn == ENTER){
        	InsertNV(dsnv,nhanvien);

			p = 1;
			return 1;
		}

    }while(pn!=ESC);
    return p;
}
int ChinhSuaNhanVien(DSNhanVien &dsnv,NhanVien *nhanvien)
{
    int x = 161 ; int y = 26;
    char pn = 17;
    ClearInsideBox(23,39,166,199);//Xoa man hinh edit
    Caption(captionNV,SizeofCaptionNV,x,y);
    NhanVien nv = *nhanvien;
    NhapNV(x,y,1,pn,nv,dsnv);
    if(pn ==ENTER){
    	*nhanvien = nv;
    	ThongBao("Du lieu da duoc cap nhat");
    	return 1;
	}
    return 0;
}
void Lietke(DSNhanVien ds){
    for(int i=0;i<ds.Size;i++)
    cout<<ds.DsNhanVien[i]->TEN<<endl;
}

int KiemTraNV(NhanVien nv){
    if(nv.HO==""||nv.TEN==""||nv.MANV=="")
        return false;
    return true;
}

string MaNV = "", Ho = "", Ten = "", Phai = "";

void ReadDataNhanVien(string line){
	string newString = "";
	int i = 0;
	getData(i, line, newString);
	MaNV = newString;
	newString = "";
	i++;
	getData(i, line, newString);
	Ho = newString;
	newString = "";
	i++;
	getData(i, line, newString);
	Ten = newString;
	newString = "";
	i++;
	getData(i, line, newString);
	Phai = newString;
}

void ReadFileNhanVien(DSNhanVien &ds){
	ifstream read;
	string line;
	read.open("DataNhanVien.txt",ios::in);
	char data[100];
	int i = 0;
	ds.Size = 0;
	string s = "";
	while(getline(read, line)){
		if(line[0] == '-'){
			break;
		}
		MaNV = "";
		Ho = "";
		Ten = "";
		Phai = "";
		ReadDataNhanVien(line);
		NhanVien newNV;
		newNV.MANV = MaNV;
		newNV.HO = Ho;
		newNV.TEN = Ten;
		newNV.PHAI = Phai;
		InsertNV(ds, newNV);
		string tempTEN = Ten;
		for(int i = 0; i < tempTEN.size(); i++){
			if(tempTEN[i] >= 97 && tempTEN[i] <= 122){
				tempTEN[i] -= 32;
			}
		}

	}
	read.close();
	SortNV(ds);

}
void WriteDataNhanVien(DSNhanVien &ds){
	ofstream write;
	write.open("DataNhanVien.txt",ios::trunc);
	for(int i = 0; i < ds.Size; i++){
		write << ds.DsNhanVien[i]->MANV;
		write << ",";
		write << ds.DsNhanVien[i]->HO;
		write << ",";
		write << ds.DsNhanVien[i]->TEN;
		write << ",";
		write << ds.DsNhanVien[i]->PHAI;
		write << ",\n";
	}
	write << "-";
	write.close();
}

void indanhsachnhanvien(DSNhanVien &ds,DSNhanVien dsnv, int nextX, int stt, int trang, int sotrang, int sl)
{
	if(trang == 1)
	{
		stt = 1;
	}
	else
	{
		stt = 10 * (trang - 1) + 1;
	}
	DrawBorderList(35, 10, 11, 5, 20, 1);
	DrawDetail("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh", "");
	for(int i = 0 + (trang - 1) * 10; i < 10 + (trang - 1) * 10 && i < sl; i++){
		gotoxy(36 + nextX, 13 + (i % 10) * 2);
		cout << stt;
		stt++;
		nextX += 20;
		gotoxy(36 + nextX, 13 + (i % 10) * 2);
		cout << ds.DsNhanVien[i]->MANV;
		nextX += 20;
		gotoxy(36 + nextX, 13 + (i % 10) * 2);
		cout << ds.DsNhanVien[i]->HO;
		nextX += 20;
		gotoxy(36 + nextX, 13 + (i % 10) * 2);
		cout << ds.DsNhanVien[i]->TEN;
		nextX += 20;
		gotoxy(36 + nextX, 13 + (i % 10) * 2);
		cout << ds.DsNhanVien[i]->PHAI;
		nextX = 0;

	}
	gotoxy(80, 36);
	cout << "[<-] Tro lai | Tiep Theo [->]";
	gotoxy(125, 34);
	cout << "Trang: " << trang << "/" << sotrang;
}

int printdsNhanVien(DSNhanVien &ds, DSNhanVien dsnv, int loai) // 0: nhanvien, 1: hoadon
{
	ShowCur(0);
	int chon_1=0;
	string nvDuocChon = "";	
	int nextX = 0;
	int stt = 1;
	int trang = 1;
	int sotrang = 1;
	int sl = ds.Size;
	if(sl <= 10)
	{
		trang = 1;
		sotrang = 1;
	}
	else
	{
		sotrang = sl / 11 + 1;
	}
	
	int c=0;
	
	while(1)
	{
		if (loai==0)
		{
			Print:
			sl = ds.Size;
			nextX = 0;		
			indanhsachnhanvien(ds,dsnv,nextX,stt,trang, sotrang,sl);

			do
			{
				c = getch();
			}while(c != KLEFT && c != KRIGHT && c!= ESC && c != DEL && c != INS && c != F2);

			if(c == ESC)
			{
	        	ClearInsideBox(1, 34, 21, 160);// xoa man hinh chinh
	        	return -1;
			}
	 
			else if(c == KLEFT)
			{
				if(sotrang > 1 && trang > 1)
				{
					ClearFunction();
					DrawBorderList(35, 10, 11, 5, 20, 1);
					DrawDetail("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh", "");
					stt -= (10 + stt % 10);
					stt += 1;
					trang--;
					goto Print;
				}
				else
				{
					stt = 1;
				}
			}
			
			else if(c == KRIGHT)
			{
				if(sotrang > 1 && trang < sotrang)
				{
					ClearFunction();
					DrawBorderList(35, 10, 11, 5, 20, 1);
					DrawDetail("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh", "");
					trang++;
					goto Print;
				}
				else
				{
					stt = sl / 10;
					stt = stt * 10 + 1;
				}
			}
		}
		
		if((c == F2 && loai==0) || (c == DEL && loai==0) || loai==1)
		{
			ClearInsideBox(1, 34, 21, 160);
			Print1:
			indanhsachnhanvien(ds,dsnv,nextX,stt,trang, sotrang,sl);
			nvDuocChon= "";
			char pn = 0;
			int x = 35;
			int y = 13;
			int dem = 0;
			int lpn = 0;
			int sl = 0;
			int chon = 0;
			int chon_1=trang*10-9;
			string sosanh = "";
			gotoxy(x+105,y);
			cout << "[<=]";
		    while(true)
		    {
		    	pn = getch();
		        if(pn==-32)
		        {
		            pn = getch();
		            lpn = 1;
		        }
		        pn = toupper(pn);
		        
		        /// di chuyen chon nhan vien
		        if(lpn==1 && (pn == UP || pn==DOWN || pn ==KLEFT || pn == KRIGHT) || pn == ENTER || pn==ESC) 
		        {
					switch(pn)
			        {
			            case UP:
							if(chon > 0){
								gotoxy(x+105,y+2*chon);
								cout << "     ";
								chon--;
								gotoxy(x+105,y+2*chon);
								cout << "[<=]";
								chon_1--;
							}
							break;
							
			            case DOWN:
							if(chon < 9){
								gotoxy(x+105,y+2*chon);
								cout << "    ";
								chon ++ ;
								gotoxy(x+105,y+2*chon);
								cout << "[<=]";
								chon_1++;
							}
						 	break;
						 	
						case KLEFT:
						{
							if(sotrang > 1 && trang > 1)
							{
								ClearFunction();
								DrawBorderList(35, 10, 11, 5, 20, 1);
								DrawDetail("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh", "");
								stt -= (10 + stt % 10);
								stt += 1;
								trang--;
								goto Print1;
							}
							else
							{
								stt = 1;
							}
							
						}
						
						case KRIGHT:
						{
							if(sotrang > 1 && trang < sotrang)
							{
								ClearFunction();
								DrawBorderList(35, 10, 11, 5, 20, 1);
								DrawDetail("STT", "Ma nhan vien", "Ho", "Ten", "Gioi tinh", "");
								trang++;
								goto Print1;
							}
							else
							{
								stt = sl / 10;
								stt = stt * 10 + 1;
							}
						}
									
						case ENTER:
				        {
				        	if (loai==0)
				        	{
				        		if (c==F2)
					        	{
					        		ShowCur(1);
									// tim nhanvien
									NhanVien *nv;
									nvDuocChon = ds.DsNhanVien[chon_1-1]->MANV;
									int pos = SeachNV(ds,nvDuocChon);
									if(pos != -1)
									{
										nv = ds.DsNhanVien[pos];
										int x = ChinhSuaNhanVien(ds, nv);
										SortNV(ds);
										WriteDataNhanVien(ds);
										if(x != 0)
										{
											ClearInsideBox(23,39,161,206);//Xoa man hinh edit
											ThongBao("Da sua du lieu thanh cong");
										}
									}
									else
									{
										ClearInsideBox(23,39,161,206);//Xoa man hinh edit
										ThongBao("Nhan Vien khong ton tai trong danh sach");
									}
									sleep(1);
									ClearFunction();
								}
								
								if (c==DEL)
					        	{
					        		//ShowCur(1);					
									nvDuocChon = ds.DsNhanVien[chon_1-1]->MANV;
									int pos = SeachNV(dsnv,nvDuocChon);
						
									if(pos != -1)
									{
										if(dsnv.DsNhanVien[pos]->DSHoaDon!=NULL)
								        {
								            ThongBao("Nhan vien da lap hoa don nen khong the xoa");
								        }
								        else
								        {
								            if(CoHayKhong("Ban co chac muon xoa " + dsnv.DsNhanVien[pos]->HO + " " + dsnv.DsNhanVien[pos]->TEN + " "))
											{
								            	int x = RemoveNV(ds, nvDuocChon);
								                WriteDataNhanVien(ds);
								                if(x == 1)
												{
								                    ClearInsideBox(23,39,161,206);//Xoa man hinh edit
								                    ThongBao("Da xoa khoi danh sach");
								                }
								                sleep(1);
											}
									    }
									}		
								}
							}
							
					        else
					        {
					        	ShowCur(1);
								// tim nhanvien	
								NhanVien *nv;
								nvDuocChon = ds.DsNhanVien[chon_1-1]->MANV;
								int pos = SeachNV(ds,nvDuocChon);
								return pos;
							}
						}
						
						case ESC:
						{
				        	ClearInsideBox(1, 34, 21, 160);// xoa man hinh chinh
				        	if (loai==0)
				        	goto Print;
				        	else
				        	return -1;
						}
				    }
			    
				gotoxy(125, 36);
				cout << "        ";
				gotoxy(125, 36);
				cout << "Chon: " << chon_1;			            
				lpn = 0;
				}		
			}
		}
	
		if (c == INS && loai == 0)
		{
			ShowCur(1);
			int x =ThemMoiNhanVien(ds);
			SortNV(ds);
			WriteDataNhanVien(ds);
			if (x == 1)
			{
				ThongBao("Da them vao danh sach");
			}
	
			sleep(1);
			stt = 1;
			ClearFunction();
		}
	}
}


#endif // NHANVIEN_H_INCLUDED
