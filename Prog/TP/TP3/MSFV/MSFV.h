/* --------------------------------------------------------------------------------------
*   Inclusions
* ----------------------------------------------------------------------------------- */

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "Parametres.h"

/* --------------------------------------------------------------------------------------
*   Constantes
* ----------------------------------------------------------------------------------- */

#define FENETRE_LARGEUR iLargeurFenetre
#define FENETRE_HAUTEUR iHauteurFenetre

#define ICONE_DOSSIER 1
#define ICONE_FICHIER 2
#define ICONE_COMPRESSE 4

#define MENU_AUCUN 0
#define MENU_NOUVEAU_DOSSIER 1
#define MENU_NOUVEAU_FICHIER 2
#define MENU_RENOMMER 4
#define MENU_SUPPRIMER 8
#define MENU_COMPRESSER 16
#define MENU_DECOMPRESSER 32
#define MENU_SELECTIONNER_TOUT 64
#define MENU_TOUS 127

#define BOUTON_GAUCHE SDL_BUTTON_LEFT
#define BOUTON_DROITE SDL_BUTTON_RIGHT

/* --------------------------------------------------------------------------------------
*  Fonctions globales
* ----------------------------------------------------------------------------------- */

int iLargeurFenetre, iHauteurFenetre;bool boCTRL;SDL_Window* pSDLWindow;SDL_Renderer* pSDLRenderer;TTF_Font* pStringFont;SDL_Surface* pTempSDLSurface;SDL_Texture* pFolderSDLTexture;SDL_Texture* pStateSDLTexture;SDL_Texture* pFileSDLTexture;SDL_Texture* pSelectedFileSDLTexture;SDL_Texture* pCompressSDLTexture;SDL_Texture* pSelectedCompressSDLTexture;SDL_Texture* pSelectedFolderSDLTexture;SDL_Texture* pStringTexture;SDL_Event Event;bool boExecution;
void OnRefresh(void);
void Init(int _iLargeur, int _iHauteur){ SDL_Init(SDL_INIT_VIDEO); TTF_Init(); iLargeurFenetre = _iLargeur; iHauteurFenetre = _iHauteur; pSDLWindow = SDL_CreateWindow("MSFV://", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _iLargeur, _iHauteur, SDL_WINDOW_RESIZABLE); SDL_SetWindowMinimumSize(pSDLWindow, 640, 480); pSDLRenderer = SDL_CreateRenderer(pSDLWindow, -1, 0); SDL_SetRenderDrawColor(pSDLRenderer, 255, 255, 255, 255); pTempSDLSurface = SDL_LoadBMP(CHEMIN_IMAGE_DOSSIER); pFolderSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pTempSDLSurface = SDL_LoadBMP(CHEMIN_IMAGE_DOSSIER_SELECTIONNE); pSelectedFolderSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pTempSDLSurface = SDL_LoadBMP(CHEMIN_IMAGE_FICHIER); pFileSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pTempSDLSurface = SDL_LoadBMP(CHEMIN_IMAGE_FICHIER_SELECTIONNE); pSelectedFileSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pTempSDLSurface = SDL_LoadBMP(CHEMIN_IMAGE_COMPRESSE); pCompressSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pTempSDLSurface = SDL_LoadBMP(CHEMIN_IMAGE_COMPRESSE_SELECTIONNE); pSelectedCompressSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pTempSDLSurface = SDL_CreateRGBSurface(0, 50, 20, 32, 0, 0, 0, 0); SDL_FillRect(pTempSDLSurface, NULL, 0xDDDDDD); pStateSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pTempSDLSurface); SDL_FreeSurface(pTempSDLSurface); pStringFont = TTF_OpenFont(CHEMIN_POLICE_CARACTERES, 12); boCTRL = false; boExecution = true; }
void DessinerTitre(const char* _strTitre){SDL_SetWindowTitle(pSDLWindow,_strTitre);}
void DessinerIcone(int _iX,int _iY,unsigned int _uiIcone,bool _boSelectionne){SDL_Rect PositionRect={_iX,_iY,ICONE_LARGEUR,ICONE_HAUTEUR};SDL_Texture* pSDLTexture=nullptr;switch(_uiIcone){case ICONE_DOSSIER:(_boSelectionne)?pSDLTexture=pSelectedFolderSDLTexture:pSDLTexture=pFolderSDLTexture;break;case ICONE_FICHIER:(_boSelectionne)?pSDLTexture=pSelectedFileSDLTexture:pSDLTexture=pFileSDLTexture;break;case ICONE_COMPRESSE:(_boSelectionne)?pSDLTexture=pSelectedCompressSDLTexture:pSDLTexture=pCompressSDLTexture;break;}if(pSDLTexture!=nullptr)SDL_RenderCopy(pSDLRenderer,pSDLTexture,NULL,&PositionRect);}
void DessinerChaine(const char* _strTexte,int _iX,int _iY){int iW,iH;TTF_SizeText(pStringFont,_strTexte,&iW,&iH);SDL_Rect PositionRect={_iX,_iY,iW,iH};SDL_Color StringColor={0,0,0};pTempSDLSurface=TTF_RenderText_Solid(pStringFont,_strTexte,StringColor);pStringTexture=SDL_CreateTextureFromSurface(pSDLRenderer,pTempSDLSurface);SDL_RenderCopy(pSDLRenderer,pStringTexture,NULL,&PositionRect);SDL_FreeSurface(pTempSDLSurface);SDL_DestroyTexture(pStringTexture);}
int LargeurChaine(const char* _strChaine){int iW,iH;TTF_SizeText(pStringFont,_strChaine,&iW,&iH);return iW;}
void DessinerBarreEtat(unsigned int _uiNbrElements,unsigned int _uiNbrSelections){SDL_Rect PositionRect={iLargeurFenetre-50,iHauteurFenetre-20,50,20};SDL_RenderCopy(pSDLRenderer,pStateSDLTexture,NULL,&PositionRect);char strElements[5],strSelections[5];_itoa_s(_uiNbrElements,strElements,10);_itoa_s(_uiNbrSelections,strSelections,10);DessinerChaine(strSelections,PositionRect.x+10,iHauteurFenetre-15);DessinerChaine("/",PositionRect.x+25,iHauteurFenetre-15);DessinerChaine(strElements,PositionRect.x+35,iHauteurFenetre-15);}
void OnMouseClick(int _iX, int _iY, unsigned char _ucButton, bool _boCTRL);
bool Execution(){SDL_RenderClear(pSDLRenderer);OnRefresh();SDL_RenderPresent(pSDLRenderer);while(SDL_PollEvent(&Event))switch(Event.type){case SDL_KEYUP:if((Event.key.keysym.sym==SDLK_LCTRL)||(Event.key.keysym.sym==SDLK_RCTRL))boCTRL=false;break;case SDL_KEYDOWN:if((Event.key.keysym.sym==SDLK_LCTRL)||(Event.key.keysym.sym==SDLK_RCTRL))boCTRL=true;break;case SDL_MOUSEBUTTONUP:int iX,iY;SDL_GetMouseState(&iX,&iY);OnMouseClick(iX,iY,Event.button.button,boCTRL);break;case SDL_WINDOWEVENT:SDL_GetWindowSize(pSDLWindow,&iLargeurFenetre,&iHauteurFenetre);break;case SDL_QUIT:SDL_DestroyTexture(pFolderSDLTexture);SDL_DestroyTexture(pFileSDLTexture);SDL_DestroyTexture(pSelectedFileSDLTexture);SDL_DestroyTexture(pSelectedFolderSDLTexture);SDL_DestroyTexture(pCompressSDLTexture);SDL_DestroyTexture(pSelectedCompressSDLTexture);TTF_CloseFont(pStringFont);TTF_Quit();SDL_Quit();boExecution=false;break;}return boExecution;}

/* --------------------------------------------------------------------------------------
*   Classes
* ----------------------------------------------------------------------------------- */

class CMenu{ private:bool m_boExecution; SDL_Rect m_PositionRect; SDL_Rect m_SelectedPositionRect; SDL_Texture* m_pSDLTexture; SDL_Texture* m_pSDLSelectedTexture; int m_iSelectedIindex; public:CMenu(); ~CMenu(); int ShowDialog(int _iX, int _iY, unsigned int _uiEnabled); }; CMenu::CMenu(){ m_boExecution = false; m_PositionRect.w = 150; m_PositionRect.h = 204; SDL_Surface* pSDLSurface = SDL_CreateRGBSurface(0, m_PositionRect.w, m_PositionRect.h, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000); SDL_FillRect(pSDLSurface, NULL, 0x888888); SDL_Rect ItemRect = { 1, 1, 148, 28 }; for (int i = 0; i<7; i++){ SDL_FillRect(pSDLSurface, &ItemRect, 0xBBBBBB); ItemRect.y += 29; }m_pSDLTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pSDLSurface); SDL_FreeSurface(pSDLSurface); pSDLSurface = SDL_CreateRGBSurface(0, 147, 27, 32, 0xFF0000, 0x00FF00, 0x0000FF, 0x000000); SDL_FillRect(pSDLSurface, NULL, 0xDDDDDD); m_pSDLSelectedTexture = SDL_CreateTextureFromSurface(pSDLRenderer, pSDLSurface); SDL_FreeSurface(pSDLSurface); m_SelectedPositionRect.x = 1; m_SelectedPositionRect.y = 0; m_SelectedPositionRect.w = 147; m_SelectedPositionRect.h = 27; m_iSelectedIindex = -1; }CMenu::~CMenu(){ SDL_DestroyTexture(m_pSDLTexture); }int CMenu::ShowDialog(int _iX, int _iY, unsigned int _uiEnabled){ m_boExecution = true; m_iSelectedIindex = -1; while (m_boExecution){ SDL_RenderClear(pSDLRenderer); OnRefresh(); m_PositionRect.x = _iX; m_PositionRect.y = _iY; SDL_RenderCopy(pSDLRenderer, m_pSDLTexture, NULL, &m_PositionRect); if ((m_iSelectedIindex >= 0) && ((_uiEnabled&(1 << m_iSelectedIindex)) == (1 << m_iSelectedIindex))){ m_SelectedPositionRect.x = _iX + 1; m_SelectedPositionRect.y = _iY + 1 + m_iSelectedIindex * 29; SDL_RenderCopy(pSDLRenderer, m_pSDLSelectedTexture, NULL, &m_SelectedPositionRect); }DessinerChaine("Nouveau dossier...", m_PositionRect.x + 10, m_PositionRect.y + 8); DessinerChaine("Nouveau fichier...", m_PositionRect.x + 10, m_PositionRect.y + 8 + 29); DessinerChaine("Renommer...", m_PositionRect.x + 10, m_PositionRect.y + 8 + 29 * 2); DessinerChaine("Supprimer", m_PositionRect.x + 10, m_PositionRect.y + 8 + 29 * 3); DessinerChaine("Compresser", m_PositionRect.x + 10, m_PositionRect.y + 8 + 29 * 4); DessinerChaine("Décompresser", m_PositionRect.x + 10, m_PositionRect.y + 8 + 29 * 5); DessinerChaine("Tout sélectionner", m_PositionRect.x + 10, m_PositionRect.y + 8 + 29 * 6); SDL_RenderPresent(pSDLRenderer); int iX, iY; while (SDL_PollEvent(&Event))switch (Event.type){ case SDL_MOUSEMOTION:SDL_GetMouseState(&iX, &iY); if ((iX<m_PositionRect.x) || (iX>m_PositionRect.x + m_PositionRect.w) || (iY<m_PositionRect.y) || (iY>m_PositionRect.y + m_PositionRect.h)){ m_boExecution = false; m_iSelectedIindex = -1; } else{ if ((iY - m_PositionRect.y)>(m_PositionRect.h - m_SelectedPositionRect.h))m_iSelectedIindex = 6; else if ((iY - m_PositionRect.y)>(m_PositionRect.h - (m_SelectedPositionRect.h) * 2))m_iSelectedIindex = 5; else if ((iY - m_PositionRect.y)>(m_PositionRect.h - (m_SelectedPositionRect.h + 2) * 3))m_iSelectedIindex = 4; else if ((iY - m_PositionRect.y)>(m_PositionRect.h - (m_SelectedPositionRect.h + 2) * 4))m_iSelectedIindex = 3; else if ((iY - m_PositionRect.y)>(m_PositionRect.h - (m_SelectedPositionRect.h + 2) * 5))m_iSelectedIindex = 2; else if ((iY - m_PositionRect.y)>(m_PositionRect.h - (m_SelectedPositionRect.h + 2) * 6))m_iSelectedIindex = 1; else if ((iY - m_PositionRect.y)>(m_PositionRect.h - (m_SelectedPositionRect.h + 2) * 7))m_iSelectedIindex = 0; else m_iSelectedIindex = -1; }break; case SDL_MOUSEBUTTONUP:if ((_uiEnabled&(1 << m_iSelectedIindex)) == (1 << m_iSelectedIindex))m_boExecution = false; break; case SDL_WINDOWEVENT:SDL_GetWindowSize(pSDLWindow, &iLargeurFenetre, &iHauteurFenetre); break; } }return 1 << m_iSelectedIindex; }
class CMSFVWindow { private:TTF_Font* m_TTFFontTitle; SDL_Texture* m_SDLTextureTitle; protected:SDL_Renderer* m_pSDLRenderer; SDL_Texture* m_pSDLTexture; SDL_Rect m_SDLRect, m_SDLRectTitle; virtual void SetPosition(void) { SDL_GetWindowSize(pSDLWindow, &iLargeurFenetre, &iHauteurFenetre); m_SDLRect.x = iLargeurFenetre / 2 - m_SDLRect.w / 2; m_SDLRect.y = iHauteurFenetre / 2 - m_SDLRect.h / 2; m_SDLRectTitle.x = m_SDLRect.x + 10; m_SDLRectTitle.y = m_SDLRect.y + 8; }public:CMSFVWindow(SDL_Renderer* _pSDLRenderer, unsigned int _uiWidth, unsigned int _uiHeight) { m_pSDLRenderer = _pSDLRenderer; m_TTFFontTitle = TTF_OpenFont(CHEMIN_POLICE_CARACTERES_TITRE, 14); SDL_Surface* pSDLSurface = SDL_CreateRGBSurface(0, _uiWidth, _uiHeight, 32, 0, 0, 0, 0); SDL_Rect SDLRects[5] = { { 0, 0, _uiWidth, _uiHeight }, { 1, 1, _uiWidth - 2, _uiHeight - 2 }, { 8, 30, _uiWidth - 16, _uiHeight - 38 }, { 9, 31, _uiWidth - 18, _uiHeight - 40 }, { _uiWidth - 50, 1, 41, 20 } }; unsigned int SDLColors[5] = { 0x737373, 0x939393, 0x808080, 0xFFFFFF, 0xC75050 }; for (int i = 0; i < 5; i++) SDL_FillRect(pSDLSurface, &SDLRects[i], SDLColors[i]); m_pSDLTexture = SDL_CreateTextureFromSurface(_pSDLRenderer, pSDLSurface); SDL_FreeSurface(pSDLSurface); m_SDLRect.x = m_SDLRect.y = 1; m_SDLRect.w = _uiWidth; m_SDLRect.h = _uiHeight; m_SDLRectTitle.x = m_SDLRectTitle.y = 5; }void SetTitle(string _strTitle) { if (!_strTitle.empty()) { SDL_Surface* pSDLSurfaceTitle; TTF_SizeText(m_TTFFontTitle, _strTitle.c_str(), &m_SDLRectTitle.w, &m_SDLRectTitle.h); pSDLSurfaceTitle = TTF_RenderText_Solid(m_TTFFontTitle, _strTitle.c_str(), { 255, 255, 255 }); SDL_DestroyTexture(m_SDLTextureTitle); m_SDLTextureTitle = SDL_CreateTextureFromSurface(m_pSDLRenderer, pSDLSurfaceTitle); SDL_FreeSurface(pSDLSurfaceTitle); } }virtual string ShowDialog(void) { SDL_RenderCopy(m_pSDLRenderer, m_pSDLTexture, NULL, &m_SDLRect); SDL_RenderCopy(m_pSDLRenderer, m_SDLTextureTitle, NULL, &m_SDLRectTitle); return ""; }~CMSFVWindow() { SDL_DestroyTexture(m_pSDLTexture); } };
class CMSFVTextBox : public CMSFVWindow { private:SDL_Texture* m_pSDLTextureDialog, *m_SDLTextureText; SDL_Rect m_SDLRectTextBox, m_SDLRectText; TTF_Font* m_TTFFontText; string m_strText; char m_chrKeyDown; bool m_boShift; void SetPosition(void) { CMSFVWindow::SetPosition(); m_SDLRectTextBox.x = m_SDLRect.x + 25; m_SDLRectTextBox.y = m_SDLRect.y + 55; m_SDLRectText.x = m_SDLRect.x + 30; m_SDLRectText.y = m_SDLRect.y + 60; m_SDLRectTextBox.w = 550; m_SDLRectTextBox.h = 25; }public:CMSFVTextBox(SDL_Renderer* _pSDLRenderer) : CMSFVWindow(_pSDLRenderer, 600, 112) { SDL_Surface* pSDLSurface = SDL_CreateRGBSurface(0, 500, 25, 32, 0, 0, 0, 0); SDL_Rect SDLRects[2] = { { 0, 0, 500, 25 }, { 1, 1, 498, 23 } }; unsigned int SDLColors[2] = { 0x737373, 0xFFFFFF }; for (int i = 0; i < 2; i++) SDL_FillRect(pSDLSurface, &SDLRects[i], SDLColors[i]); m_pSDLTextureDialog = SDL_CreateTextureFromSurface(m_pSDLRenderer, pSDLSurface); SDL_FreeSurface(pSDLSurface); m_TTFFontText = TTF_OpenFont(CHEMIN_POLICE_CARACTERES, 12); m_chrKeyDown = '\0'; m_boShift = false; }void SetText(string _strText) { m_strText = _strText; SDL_Surface* pSDLSurfaceText; TTF_SizeText(m_TTFFontText, m_strText.c_str(), &m_SDLRectText.w, &m_SDLRectText.h); pSDLSurfaceText = TTF_RenderText_Solid(m_TTFFontText, m_strText.c_str(), { 0, 0, 0 }); SDL_DestroyTexture(m_SDLTextureText); m_SDLTextureText = SDL_CreateTextureFromSurface(m_pSDLRenderer, pSDLSurfaceText); SDL_FreeSurface(pSDLSurfaceText); }string ShowDialog() { SetPosition(); bool boLoop = true; SDL_Event SDLEvent; while (boLoop){ SDL_RenderClear(m_pSDLRenderer); OnRefresh(); CMSFVWindow::ShowDialog(); SDL_RenderCopy(m_pSDLRenderer, m_pSDLTextureDialog, NULL, &m_SDLRectTextBox); SDL_RenderCopy(m_pSDLRenderer, m_SDLTextureText, NULL, &m_SDLRectText); SDL_RenderPresent(m_pSDLRenderer); while (SDL_PollEvent(&SDLEvent)){ switch (SDLEvent.type){ case SDL_WINDOWEVENT:SetPosition(); break; case SDL_KEYUP:if ((SDLEvent.key.keysym.sym == SDLK_RSHIFT) || (SDLEvent.key.keysym.sym == SDLK_LSHIFT))m_boShift = false; else m_chrKeyDown = '\0'; break; case SDL_KEYDOWN:switch (SDLEvent.key.keysym.sym) { case SDLK_LSHIFT: case SDLK_RSHIFT: m_boShift = true; break; case SDLK_RETURN:boLoop = false; break; case SDLK_ESCAPE: m_strText.clear(); boLoop = false; break; case SDLK_BACKSPACE:if (SDLEvent.key.keysym.sym != m_chrKeyDown) { if (!m_strText.empty()) m_strText.pop_back(); m_chrKeyDown = SDLEvent.key.keysym.sym; SetText(m_strText); }break; default:if (SDLEvent.key.keysym.sym != m_chrKeyDown) { if (m_strText.length() < 49) { if (m_boShift) SDLEvent.key.keysym.sym = toupper(SDLEvent.key.keysym.sym); m_strText.push_back(SDLEvent.key.keysym.sym); m_chrKeyDown = SDLEvent.key.keysym.sym; SetText(m_strText); } } }break; }break; } }return m_strText; }~CMSFVTextBox() { SDL_DestroyTexture(m_pSDLTextureDialog); } };
class CMSFVMemo : public CMSFVWindow { private:SDL_Texture* m_pSDLTextureDialog; SDL_Rect m_SDLRectMemo, m_SDLRectText; TTF_Font* m_TTFFontText; string m_strText[23]; SDL_Texture* m_SDLTextureText[23]; char m_chrKeyDown; unsigned int m_uiLigne; bool m_boShift; void SetPosition(void) { CMSFVWindow::SetPosition(); m_SDLRectMemo.x = m_SDLRect.x + 25; m_SDLRectMemo.y = m_SDLRect.y + 50; m_SDLRectText.x = m_SDLRect.x + 30; }void SetLine(unsigned int _uiLine) { if (!m_strText[_uiLine].empty()) { SDL_Surface* pSDLSurfaceText; TTF_SizeText(m_TTFFontText, m_strText[_uiLine].c_str(), &m_SDLRectText.w, &m_SDLRectText.h); pSDLSurfaceText = TTF_RenderText_Solid(m_TTFFontText, m_strText[_uiLine].c_str(), { 0, 0, 0 }); SDL_DestroyTexture(m_SDLTextureText[_uiLine]); m_SDLTextureText[_uiLine] = SDL_CreateTextureFromSurface(m_pSDLRenderer, pSDLSurfaceText); SDL_FreeSurface(pSDLSurfaceText); } }public:CMSFVMemo(SDL_Renderer* _pSDLRenderer) : CMSFVWindow(_pSDLRenderer, 600, 400) { m_SDLRectMemo.w = 550; m_SDLRectMemo.h = 325; SDL_Surface* pSDLSurface = SDL_CreateRGBSurface(0, 550, 325, 32, 0, 0, 0, 0); SDL_Rect SDLRects[2] = { { 0, 0, 550, 25 }, { 1, 1, 548, 323 } }; unsigned int SDLColors[2] = { 0x737373, 0xFFFFFF }; for (int i = 0; i < 2; i++) SDL_FillRect(pSDLSurface, &SDLRects[i], SDLColors[i]); m_pSDLTextureDialog = SDL_CreateTextureFromSurface(m_pSDLRenderer, pSDLSurface); SDL_FreeSurface(pSDLSurface); m_TTFFontText = TTF_OpenFont(CHEMIN_POLICE_CARACTERES, 12); m_chrKeyDown = '\0'; m_uiLigne = 0; m_boShift = false; }void SetText(string _strText) { int iW = 0, iH = 0; for (unsigned uiLigne = 0; uiLigne < 23; uiLigne++) m_strText[uiLigne].clear(); m_uiLigne = 0; for (unsigned int uiChar = 0; uiChar < _strText.length(); uiChar++) { TTF_SizeText(m_TTFFontText, m_strText[m_uiLigne].c_str(), &iW, &iH); if (m_uiLigne < 23) (_strText[uiChar] == '\n') ? m_uiLigne++ : m_strText[m_uiLigne].push_back(_strText[uiChar]); if (iW > 526) m_uiLigne++; }for (int i = 0; i < 23; i++) SetLine(i); if (m_uiLigne > 22) m_uiLigne = 22; while (m_strText[m_uiLigne].empty() && (m_uiLigne > 0)) m_uiLigne--; }string ShowDialog(void) { SetPosition(); bool boLoop = true; SDL_Event SDLEvent; while (boLoop){ SDL_RenderClear(m_pSDLRenderer); OnRefresh(); CMSFVWindow::ShowDialog(); SDL_RenderCopy(m_pSDLRenderer, m_pSDLTextureDialog, NULL, &m_SDLRectMemo); for (int i = 0; i < 23; i++) { m_SDLRectText.y = i * m_SDLRectText.h + m_SDLRect.y + 52; TTF_SizeText(m_TTFFontText, m_strText[i].c_str(), &m_SDLRectText.w, &m_SDLRectText.h); SDL_RenderCopy(m_pSDLRenderer, m_SDLTextureText[i], NULL, &m_SDLRectText); }SDL_RenderPresent(m_pSDLRenderer); int iW, iH; while (SDL_PollEvent(&SDLEvent)){ switch (SDLEvent.type){ case SDL_WINDOWEVENT:SetPosition(); break; case SDL_KEYUP: if ((SDLEvent.key.keysym.sym == SDLK_RSHIFT) || (SDLEvent.key.keysym.sym == SDLK_LSHIFT))m_boShift = false; else m_chrKeyDown = '\0'; break; case SDL_KEYDOWN:switch (SDLEvent.key.keysym.sym) { case SDLK_LSHIFT: case SDLK_RSHIFT: m_boShift = true; break; case SDLK_RETURN:if (SDLEvent.key.keysym.sym != m_chrKeyDown) { m_chrKeyDown = SDLEvent.key.keysym.sym; if (m_uiLigne <22) m_uiLigne++; }break; case SDLK_ESCAPE: boLoop = false; break; case SDLK_BACKSPACE:if (SDLEvent.key.keysym.sym != m_chrKeyDown) { if (m_uiLigne > 22) m_uiLigne = 22; if (!m_strText[m_uiLigne].empty()) m_strText[m_uiLigne].pop_back(); m_chrKeyDown = SDLEvent.key.keysym.sym; SetLine(m_uiLigne); if (m_strText[m_uiLigne].empty() && (m_uiLigne > 0)) m_uiLigne--; }break; default:if (SDLEvent.key.keysym.sym != m_chrKeyDown) { if (m_uiLigne < 23) { if (m_boShift) SDLEvent.key.keysym.sym = toupper(SDLEvent.key.keysym.sym); m_strText[m_uiLigne].push_back(SDLEvent.key.keysym.sym); m_chrKeyDown = SDLEvent.key.keysym.sym; SetLine(m_uiLigne); TTF_SizeText(m_TTFFontText, m_strText[m_uiLigne].c_str(), &iW, &iH); if ((iW > 526) && (m_uiLigne < 23)) m_uiLigne++; } }break; }break; } } }string strReturn = ""; for (int i = 0; i < 23; i++) strReturn += m_strText[i] + '\n'; return strReturn; }~CMSFVMemo() { for (int i = 0; i < 23; i++) SDL_DestroyTexture(m_SDLTextureText[i]); SDL_DestroyTexture(m_pSDLTextureDialog); } };