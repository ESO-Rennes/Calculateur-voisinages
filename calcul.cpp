//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "calcul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormVoisinages *FormVoisinages;
//---------------------------------------------------------------------------
__fastcall TFormVoisinages::TFormVoisinages(TComponent* Owner)
	: TForm(Owner)
{
}

	const NBMAX = 3000;
	int nbpoints;
	typedef char nompoint[15];
	typedef struct {
		float poids;
		bool parcouru;
		float distance;
		int ordre;
		} t_poids;
	typedef struct {
		float poids;
		float distance;
		int ordre;
		} t_graphe;
	nompoint    points[NBMAX];
	t_graphe    graphe[NBMAX][NBMAX];
	t_poids tabpoids[NBMAX];
	int tabante[NBMAX];

void AjouterPoint(char *point)
{// verifie que point existe déjà dans le tableau points, l'ajoute sinon dans l'ordre alpha
	int ind,k;

	ind = 0;
	while (ind < nbpoints && strcmp(point,points[ind]) > 0)
		ind++;
	if (ind >= nbpoints || strcmp(point,points[ind]) < 0)
	{
		for (k=nbpoints+1; k>ind; k--)
			strcpy(points[k],points[k-1]);
		strcpy(points[ind],point);
		nbpoints++;
	}
}
int CalculerCheminPlusCourt(int depart,int arrivee,int ordmax, float valmax,bool ordaminimiser, float *distance, int *ordre)
{
	bool    fini;
	int     i,imin;
	FILE    *fds;

	for (i=0; i<nbpoints; i++)
	{
		tabpoids[i].poids = -1;
		tabpoids[i].parcouru = false;
		tabpoids[i].distance = -1;
		tabpoids[i].ordre = -1;
		tabante[i] = -1;
	}
	tabpoids[depart].poids = 0;
	tabpoids[depart].distance = 0;
	tabpoids[depart].ordre = 0;
	fini = false;
	while (!fini)
	{
// Recherche du noeud ayant le poids le plus faible
		imin = -1;
		for (i=0; i<nbpoints; i++)
		{
			if (!tabpoids[i].parcouru && (imin == -1 || tabpoids[i].poids < tabpoids[imin].poids))
			{
				if (tabpoids[i].poids > -1 &&
					(valmax < 0 || tabpoids[i].distance <= valmax) &&
					(ordmax < 0 || tabpoids[i].ordre <= ordmax))
					imin = i;
			}
		}
		tabpoids[imin].parcouru = true;
		if (imin == arrivee)
			fini = true;
		else if (imin == -1)
		{
			*ordre = -1;
			*distance = -1;
			return(-1);
		}
		else if ((!ordaminimiser && valmax > 0 && tabpoids[imin].distance > valmax) ||
				 (ordaminimiser && ordmax > 0 && tabpoids[imin].ordre > ordmax))
		{
			*ordre = -2;
			*distance = -2;
			return(-2);
		}
		else
		{
// liste des voisins de imin
			for (i=0; i<nbpoints; i++)
			{
				if (graphe[imin][i].poids > 0)
				{
					if (tabpoids[i].parcouru == false)
					{
						if (tabpoids[i].poids == -1 ||
					(tabpoids[i].poids > tabpoids[imin].poids + graphe[imin][i].poids))
						{
					tabpoids[i].poids = tabpoids[imin].poids + graphe[imin][i].poids;
					tabpoids[i].distance = tabpoids[imin].distance + graphe[imin][i].distance;
					tabpoids[i].ordre = tabpoids[imin].ordre + graphe[imin][i].ordre;
							tabante[i] = imin;
						}
					}
				}
			}
		}
	}
	if (valmax > 0 && tabpoids[imin].poids > valmax)
	{
		*ordre = -2;
		*distance = -2;
		return(-2);
	}
	else
	{
		*ordre = tabpoids[imin].ordre;
		*distance = tabpoids[imin].distance;
		return(tabpoids[imin].poids);
	}
}
//---------------------------------------------------------------------------
int LireElement(FILE *fd, char *chaine,char separateur)
{
	char buf;
	char virg;
	int  arret;
	strcpy(chaine,"");
	arret = 0;
	buf = '\0';
	virg = '.';
	while (arret == 0)
	{
		if ((buf = fgetc(fd)) == EOF)
			arret = 3;
		else if (buf == separateur)
			arret = 1;
		else if (buf == '\n')
			arret = 2;
		else
		{
			if (buf == ',')
				chaine = strncat(chaine,&virg,1);
			else
				chaine = strncat(chaine,&buf,1);
		}
	}
	return arret;
}
//---------------------------------------------------------------------------
void __fastcall TFormVoisinages::ButtonNomFicEntreeClick(TObject *Sender)
{
	AnsiString  exte;
	FILE    *fde;
	char    sepe, colonne[30];
	bool    erreur;
	int     pos, resul;
//	wchar_t    strerreur = _TEXT("Erreur");

	OpenDialogNomFicEntree->Execute();
	EditNomFicEntree->Text = OpenDialogNomFicEntree->FileName.c_str();
	if ((fde = fopen(AnsiString(OpenDialogNomFicEntree->FileName).c_str(),"r")) == NULL)
		Application->MessageBox(_TEXT("Erreur d'ouverture du fichier d'entrée"), _TEXT("Erreur"),MB_OK);
	pos = EditNomFicEntree->Text.Pos(".");
	exte = EditNomFicEntree->Text.SubString(pos+1,3);
	if (strcmp(exte.c_str(),"csv") == 0 || strcmp(exte.c_str(),"CSV") == 0)
		sepe = ';';
	else
		sepe = char(9);
	erreur = false;
	resul = 0;
	cb_depart->Items->Clear();
	cb_arrivee->Items->Clear();
	cb_valeur->Items->Clear();
	cb_valeur->Items->Add("Pas de données - 1 par défaut");
	while (!erreur && resul < 2)
	{
		resul = LireElement(fde,colonne,sepe);
		cb_depart->Items->Add(colonne);
		cb_arrivee->Items->Add(colonne);
		cb_valeur->Items->Add(colonne);
	}
	fclose(fde);
	cb_depart->ItemIndex = 0;
	cb_arrivee->ItemIndex = 1;
	cb_valeur->ItemIndex = 3;

}
//---------------------------------------------------------------------------
/*//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <stdlib.h>

#include "calcul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormVoisinages *FormVoisinages;
//---------------------------------------------------------------------------
__fastcall TFormVoisinages::TFormVoisinages(TComponent* Owner)
	: TForm(Owner)
{
}



void __fastcall TFormVoisinages::FormActivate(TObject *Sender)
{
	cb_coupimp->ItemIndex = 0;
	cb_couplim->ItemIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormVoisinages::Label1Click(TObject *Sender)
{

}
*/
//---------------------------------------------------------------------------

void __fastcall TFormVoisinages::ButtonCalculerClick(TObject *Sender)
{
	int     i,j,lg,k;
	int     indd, inda, pos, resul, nbcalc, deb;
	float   poids,distance;
	float   dist;
	int     ordre;
	AnsiString  exte,exts;
	FILE    *fde,*fds;
	char    sepe,seps;
	bool    erreur, ordaminimiser;
	char    chaine[1000],depart[30],arrivee[30];
	nompoint    colonnes[30];
	int         nbcol,indcol;
	int         ordmax;
	float       valmax;

	if (EditNomFicEntree->Text == "")
		Application->MessageBox(_TEXT("Saisir un fichier en entrée"), _TEXT("Erreur"), MB_OK);
	else if (EditNomFicSortie->Text == "")
		Application->MessageBox(_TEXT("Saisir un fichier en sortie"),_TEXT("Erreur"), MB_OK);
	else
	{
		pos = EditNomFicEntree->Text.Pos(".");
		exte = EditNomFicEntree->Text.SubString(pos+1,3);
		pos = EditNomFicSortie->Text.Pos(".");
        exts = EditNomFicSortie->Text.SubString(pos+1,3);
		if ((fde = fopen(AnsiString(EditNomFicEntree->Text).c_str(),"r")) == NULL)
			Application->MessageBox(_TEXT("Erreur d'ouverture du fichier d'entrée"), _TEXT("Erreur"), MB_OK);
		else
		{
            if ((fds = fopen(AnsiString(EditNomFicSortie->Text).c_str(),"w")) == NULL)
                Application->MessageBox(_TEXT("Erreur d'ouverture du fichier de sortie"),_TEXT("Erreur"),MB_OK);
            else
            {
                if (strcmp(exte.c_str(),"csv") == 0 || strcmp(exte.c_str(),"CSV") == 0)
                    sepe = ';';
                else
					sepe = char(9);
                if (strcmp(exts.c_str(),"csv") == 0 || strcmp(exts.c_str(),"CSV") == 0)
                    seps = ';';
                else
                    seps = char(9);

                // lecture du fichier complet pour déterminer la liste des points
				erreur = false;
                //lecture 1ere ligne
				resul = 0;
				nbcol = 0;
                while (!erreur && resul < 2)
					resul = LireElement(fde,colonnes[nbcol++],sepe);
                nbpoints = 0;
                resul = 0;
                while (!erreur && resul != 3)
                {
					indcol = 0;
                    resul = 0;
                    while (!erreur && resul != 2 && resul != 3)
					{
                        resul = LireElement(fde,chaine,sepe);
                        if (indcol == cb_depart->ItemIndex)
                            strcpy(depart,chaine);
                        else if (indcol == cb_arrivee->ItemIndex)
                            strcpy(arrivee,chaine);
                        else if (indcol == (cb_valeur->ItemIndex - 1)) // 1 item de plus : la valeur par défaut proposée
							dist = atof(chaine);
                        indcol++;
					}
					AjouterPoint(depart);
                    AjouterPoint(arrivee);
				}
                fclose(fde);
				fde = fopen(AnsiString(EditNomFicEntree->Text).c_str(),"r");

				if (nbpoints > NBMAX)
					 Application->MessageBox(_TEXT("Nombre de points supérieur au maximum"), _TEXT("Erreur"), MB_OK);
				for (i=0; i<nbpoints; i++)
                {
                    for (j=0; j<nbpoints; j++)
                    {
						graphe[i][j].poids = -1;
						graphe[i][j].ordre = -1;
						graphe[i][j].distance = -1;
                    }
                }
				erreur = false;
				//lecture 1ere ligne
				resul = 0;
                while (!erreur && resul < 2)
					resul = LireElement(fde,depart,sepe);
				resul = 0;
                while (!erreur && resul != 3)
				{
                    indcol = 0;
                    resul = 0;
                    while (!erreur && resul != 2 && resul != 3)
                    {
                        resul = LireElement(fde,chaine,sepe);
                        if (indcol == cb_depart->ItemIndex)
                            strcpy(depart,chaine);
						else if (indcol == cb_arrivee->ItemIndex)
                            strcpy(arrivee,chaine);
                        else if (indcol == (cb_valeur->ItemIndex - 1)) // 1 item de plus : la valeur par défaut proposée
                            dist = atof(chaine);
						indcol++;
                    }
                    if (!erreur && resul != 3)
					{
						ordre = 1;
						if (RadioGroupMinimiser->ItemIndex == 1)
							poids = ordre;
                        else
							poids = dist;
                        indd = 0;
                        while (indd < nbpoints && strcmp(depart,points[indd]) != 0)
                            indd++;
                        if (indd >= nbpoints)
                        {
                            Application->MessageBox(_TEXT("Fichier d'entrée incorrect - valeur depart inconnue"),_TEXT("ERREUR"),MB_OK);
                            erreur = true;
						}
                        inda = 0;
                        while (inda < nbpoints && strcmp(arrivee,points[inda]) != 0)
                            inda++;
                        if (inda >= nbpoints)
                        {
                            Application->MessageBox(_TEXT("Fichier d'entrée incorrect - valeur arrivee inconnue"),_TEXT("ERREUR"),MB_OK);
							erreur = true;
                        }
						if (!erreur)
						{
							graphe[indd][inda].poids = poids;
							graphe[indd][inda].ordre = ordre;
                            graphe[indd][inda].distance = dist;
                            if (RadioGroupOriente->ItemIndex == 1)
                            {
								graphe[inda][indd].poids = poids;
                                graphe[inda][indd].ordre = ordre;
								graphe[inda][indd].distance = dist;
                            }
						}
                    }
                }
				fclose(fde);
                if (!erreur)
                {
                    if (RadioGroupOrdreMax->ItemIndex == 1)
						ordmax = -1;
                    else
						ordmax = UpDownOrdreMax->Position;
					if (RadioGroupValMax->ItemIndex == 1)
						valmax = -1;
					else
					{
						strcpy(chaine,AnsiString(EditValMax->Text).c_str());
						lg = strlen(chaine);
						for (i=0; i<lg; i++)
						{
							if (chaine[i] == ',')
								chaine[i] = '.';
						}
						valmax = atof(chaine);
					}
					nbcalc = nbpoints * (nbpoints-1);
					Canvas->TextOut(80,580,"Traitement en cours, veuillez patienter...");
					//(50,580,UnicodeString("              Traitement en cours           "));
					ProgressBar1->Max = nbpoints * nbpoints;
					ProgressBar1->Position = 0;
					fprintf(fds,"%s%c%s%cordre%cvaleur\n",colonnes[cb_depart->ItemIndex],seps,colonnes[cb_arrivee->ItemIndex],seps,seps);
					ordaminimiser = (RadioGroupMinimiser->ItemIndex == 1 ? true : false);
					for (i=0; i<nbpoints; i++)
					{
                        Canvas->TextOutW(300,580,i);
						if (RadioGroupOriente->ItemIndex == 1) // non oriente
							 deb = i+1;
						else
							deb = 0;
						for (j=deb; j<nbpoints; j++)
						{
						Canvas->TextOutW(300,580,i);
                        Canvas->TextOutW(330,580,j);
							if (i != j)
							{
								lg = CalculerCheminPlusCourt(i,j,ordmax,valmax,ordaminimiser,&distance,&ordre);
								if (lg >= 0 || (lg == -1 && cb_coupimp->ItemIndex == 1) || (lg == -2 && cb_couplim->ItemIndex == 1))
								{
									sprintf(chaine,"%f",distance);
									if (RadioGroupvirgule->ItemIndex == 0)
									{
										lg = strlen(chaine);
										for (k=0; k<lg; k++)
										{
											if (chaine[k] == '.')
												chaine[k] = ',';
										}
									}
									fprintf(fds,"%s%c%s%c%d%c%s\n",points[i],seps,points[j],seps,ordre,seps,chaine);
									if (RadioGroupOriente->ItemIndex == 1)
										fprintf(fds,"%s%c%s%c%d%c%s\n",points[j],seps,points[i],seps,ordre,seps,chaine);
								}
							}
							ProgressBar1->Position++;
							if (RadioGroupOriente->ItemIndex == 1)
								ProgressBar1->Position++;
						}
					}
					fclose(fds);
					Application->MessageBox(_TEXT("Traitement terminé"),_TEXT("Fin"),MB_OK);
                }
            }
		}
	 }

}
//---------------------------------------------------------------------------



void __fastcall TFormVoisinages::ButtonNomFicSortieClick(TObject *Sender)
{
	SaveDialogNomFicSortie->Execute();
	EditNomFicSortie->Text = SaveDialogNomFicSortie->FileName.c_str();
}
//---------------------------------------------------------------------------

void __fastcall TFormVoisinages::FormCreate(TObject *Sender)
{
	cb_coupimp->ItemIndex = 0;
	cb_couplim->ItemIndex = 0;
}
//---------------------------------------------------------------------------



