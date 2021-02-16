package fr.eseo.poo.projet.artiste.vue.formes;
import javax.swing.JFrame;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;
import fr.eseo.poo.projet.artiste.modele.formes.Ellipse;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class VueEllipseTest {
	public static void main(String[] args) {
		new VueEllipseTest();
	}
	
	public VueEllipseTest() {
		testEllipse();
	}
	
	
	private void testEllipse() {
		JFrame fenetre = new JFrame();
		PanneauDessin panneau = new PanneauDessin(600, 400, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);

		fenetre.setTitle("VueEllipseTest");
		fenetre.setSize(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false);
		fenetre.setAlwaysOnTop(true); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		Ellipse ell1 = new Ellipse(new Coordonnees(100, 100), 50, 30);
		VueEllipse vell1 = new VueEllipse(ell1);
		
		Ellipse ell2 = new Ellipse(new Coordonnees());
		VueEllipse vell2 = new VueEllipse(ell2);

		panneau.ajouterVueForme(vell1);
		panneau.ajouterVueForme(vell2);

		fenetre.add(panneau);
		fenetre.pack();
		fenetre.setVisible(true);
		
	}
}
