package fr.eseo.poo.projet.artiste.vue.ihm;

import java.awt.Color;
import javax.swing.JFrame;
import javax.swing.SwingUtilities;

public class PanneauDessinTest {
	
	public static void main(String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new PanneauDessinTest();
			}
		});
	}
	
	public PanneauDessinTest() {
		testConstructeur();
		testConstructeurParDefaut();
		
	}
	private void testConstructeurParDefaut() {
		JFrame fenetre = new JFrame();		
		fenetre.setTitle("Etre un Artiste");
		fenetre.setSize(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT);
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); 
		fenetre.setAlwaysOnTop(true); 
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		PanneauDessin panneau = new PanneauDessin();
		fenetre.setContentPane(panneau);
		fenetre.setVisible(true);


		
	}
	private void testConstructeur() {
		JFrame fenetre = new JFrame();
		PanneauDessin panneau = new PanneauDessin(600, 400, Color.blue);

		fenetre.setTitle("Blues du Businessman");
		//fenetre.setSize(PanneauDessin.LARGEUR_PAR_DEFAUT, PanneauDessin.HAUTEUR_PAR_DEFAUT);
		//fenetre.setSize( panneau.getWidth(), panneau.getHeight() );
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); //dimensionnement de la fenetre autorisé
		fenetre.setAlwaysOnTop(true); //placer fenetre toujours au premier plan
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);

		
		fenetre.setContentPane(panneau);
		fenetre.setVisible(true);

		
		
	}

}




