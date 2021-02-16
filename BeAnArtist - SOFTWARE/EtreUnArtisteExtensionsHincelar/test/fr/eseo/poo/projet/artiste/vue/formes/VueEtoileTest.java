package fr.eseo.poo.projet.artiste.vue.formes;

import javax.swing.JFrame;
import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Etoile;
import fr.eseo.poo.projet.artiste.modele.formes.Forme;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class VueEtoileTest {


	
	public VueEtoileTest() {
		test();
	}
	
	
	private void test() {
		JFrame fenetre = new JFrame();
		PanneauDessin panneau = new PanneauDessin(600, 400, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);

		fenetre.setTitle("VueEllipseTest");
		fenetre.setSize(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); 
		fenetre.setAlwaysOnTop(true); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		Etoile etoile1 = new Etoile(new Coordonnees(150, 150), 60, 3, Forme.PI, 1);
		VueEtoile vueetoile1 = new VueEtoile(etoile1);

		Etoile etoile2 = new Etoile(new Coordonnees(300	, 300), 60, 8, Forme.PI/6, 0.8);
		VueEtoile vueetoile2 = new VueEtoile(etoile2);
		
		Etoile etoile3 = new Etoile(new Coordonnees(300	, 150), 60, 8, 0, 0.3);
		VueEtoile vueetoile3 = new VueEtoile(etoile3);

		Etoile etoile4 = new Etoile(new Coordonnees(300	, 150), 60, 8, 0, 0.3);
		VueEtoile vueetoile4 = new VueEtoile(etoile4);
		
		Etoile etoile5 = new Etoile(30);
		VueEtoile vueetoile5 = new VueEtoile(etoile5);
		
		
		panneau.ajouterVueForme(vueetoile1);
		panneau.ajouterVueForme(vueetoile2);
		panneau.ajouterVueForme(vueetoile3);
		panneau.ajouterVueForme(vueetoile4);
		panneau.ajouterVueForme(vueetoile5);

		
		System.out.println("nombre : "+Etoile.NOMBRE_BRANCHES_PAR_DEFAUT);
		
		System.out.println("longueur : "+Etoile.LONGUEUR_BRANCHE_PAR_DEFAUT);
		System.out.println("angle : "+Etoile.ANGLE_PREMIERE_BRANCHE_PAR_DEFAUT);
		
		
		Etoile etoile = new Etoile(new Coordonnees(0,0), 50, 4, 0, 0.6);


		VueEtoile vueetoile = new VueEtoile(etoile);
		panneau.ajouterVueForme(vueetoile);	
		fenetre.add(panneau);
		fenetre.pack();
		fenetre.setVisible(true);		
	}
	
	public static void main(String[] args) {
		new VueEtoileTest();
	}
}
