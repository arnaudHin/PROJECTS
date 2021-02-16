package fr.eseo.poo.projet.artiste.controleur.outils;

import java.awt.BorderLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;

import fr.eseo.poo.projet.artiste.vue.ihm.PanneauBarreOutils;
import fr.eseo.poo.projet.artiste.vue.ihm.PanneauDessin;

public class OutilEllipseTest {

	public static void main(String[] args) {
		new OutilEllipseTest(); }
	
	public OutilEllipseTest() {
		outilEllipsetest(); }
	
	
	private void outilEllipsetest() {
		
		JFrame fenetre = new JFrame();
		JPanel content = new JPanel();
		PanneauDessin panneau = new PanneauDessin(600, 400, PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		System.out.println(panneau.getVueFormes());
		PanneauBarreOutils barreOutils = new PanneauBarreOutils(panneau);

		fenetre.setTitle("VueEllipseTest");
		fenetre.setSize(600, 400);
		//fenetre.setSize( panneau.getWidth(), panneau.getHeight() );
		fenetre.setLocationRelativeTo(null);
		fenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		fenetre.setResizable(false); //dimensionnement de la fenetre autorisé
		fenetre.setAlwaysOnTop(false); //placer fenetre toujours au premier plan
		fenetre.setBackground(PanneauDessin.COULEUR_FOND_PAR_DEFAUT);
		
		OutilEllipse outilEllipse = new OutilEllipse();
		outilEllipse.setPanneauDessin(panneau);
		panneau.associerOutil(outilEllipse);
		
		content.setLayout(new BorderLayout());	
		
		content.add(panneau, BorderLayout.WEST);
		content.add(barreOutils, BorderLayout.EAST);
		fenetre.setContentPane(content);

		fenetre.pack();
		fenetre.setVisible(true);
		
	}	
	
}







