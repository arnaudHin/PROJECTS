package fr.eseo.poo.projet.artiste.vue.ihm;

import javax.swing.JPanel;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.List;
import fr.eseo.poo.projet.artiste.controleur.outils.Outil;
import fr.eseo.poo.projet.artiste.vue.formes.VueForme;
import fr.eseo.poo.projet.artiste.modele.formes.Forme;

public class PanneauDessin extends JPanel{	

	private static final long serialVersionUID = 1L;
	public static final int LARGEUR_PAR_DEFAUT = 400;
	public static final int HAUTEUR_PAR_DEFAUT = 240;
	public static final Color COULEUR_FOND_PAR_DEFAUT = Color.white;
	
	private Outil outilCourant = null;
	private final List<VueForme> vueFormes;
	private Color couleurCourante;
	private boolean modeRemplissage;
	
	public PanneauDessin(int largeur, int hauteur, Color fond) {
		super();
		this.setPreferredSize(new Dimension(largeur, hauteur));
		this.setBackground(fond);
		this.vueFormes = new ArrayList<VueForme>();
		this.setCouleurCourante(Forme.COULEUR_PAR_DEFAUT);
		this.setModeRemplissage(false);
		this.repaint();
	}
	
	public PanneauDessin() { 
		this(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		}
	
	public List<VueForme> getVueFormes(){ 
		return this.vueFormes; 
		}
	public void ajouterVueForme(VueForme vueForme) { 
		this.vueFormes.add(vueForme); 
	}
	protected void paintComponent(Graphics g2d) {
		super.paintComponent(g2d); 
		Graphics2D g2D = (Graphics2D) g2d.create();
		for (int i=0 ; i<this.vueFormes.size() ; i++) {
			vueFormes.get(i).affiche(g2D);
		}
		g2D.dispose(); 
	}
	public void viderList() {
		this.getVueFormes().clear();
		this.repaint();
	}
	
	private void setOutilCourant(Outil outil) { 
		this.outilCourant = outil; 
		}
	public Outil getOutilCourant() {
		return this.outilCourant; 
		}
	
	public void associerOutil( Outil nouvelOutil ) {
		if(nouvelOutil != null) {
			if(this.getOutilCourant() != null) {
				dissocierOutil();
			}
			this.setOutilCourant(nouvelOutil);
			this.getOutilCourant().setPanneauDessin(this);
			this.addMouseListener(this.getOutilCourant());
			this.addMouseMotionListener(this.getOutilCourant());
		}
	}
	
	private void dissocierOutil() { 
		this.removeMouseListener(this.getOutilCourant());
		this.removeMouseMotionListener(this.getOutilCourant());
		this.getOutilCourant().setPanneauDessin(null);
		this.setOutilCourant(null);
	}
	
	public void setCouleurCourante(Color couleur) { 
		this.couleurCourante = couleur; 
		}
	public Color getCouleurCourante() { 
		return this.couleurCourante; 
		}
	
	public void setModeRemplissage(boolean modeRemplissage) { 
		this.modeRemplissage = modeRemplissage; 
		}
	public boolean getModeRemplissage() { 
		return this.modeRemplissage; 
		} 
}






