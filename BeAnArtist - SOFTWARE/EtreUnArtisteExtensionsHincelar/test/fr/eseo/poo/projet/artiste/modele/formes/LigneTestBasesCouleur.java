package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.awt.Color;
import java.util.Locale;

import javax.swing.UIManager;

import org.junit.Test;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;

public class LigneTestBasesCouleur{

	@Test
	public void testConstructeur() {
		Ligne ligne1 = new Ligne(new Coordonnees(), 1, 1);
		Ligne ligne2 = new Ligne(1, 1);
		Ligne ligne3 = new Ligne(new Coordonnees());
		Ligne ligne4 = new Ligne();
		
		assertEquals("cons 1 Mauvais x", 1, ligne1.getC2().getAbscisse(), 0.1);
		assertEquals("cons 1 Mauvais y", 1, ligne1.getC2().getOrdonnee(), 0.1);
		assertEquals("cons 2 Mauvais x", 1, ligne2.getC2().getAbscisse(), 0.1);
		assertEquals("cons 2 Mauvais y", 1, ligne2.getC2().getOrdonnee(), 0.1);
		assertEquals("cons 3 Mauvais x", 100, ligne3.getC2().getAbscisse(), 0.1);
		assertEquals("cons 3 Mauvais y", 125, ligne3.getC2().getOrdonnee(), 0.1);
		assertEquals("cons 4 Mauvais x", 100, ligne4.getC2().getAbscisse(), 0.1);
		assertEquals("cons 4 Mauvais y", 125, ligne4.getC2().getOrdonnee(), 0.1);
	}

	
	@Test
	public void testMethodes() {
		Ligne ligne = new Ligne(new Coordonnees(), 1, 0);
		assertEquals("perimetre ", 1, ligne.perimetre(), 0.1);
		ligne.deplacerVers(1, 1);
		
		assertEquals("perimetre ", 1, ligne.perimetre(), 0.1);
		assertEquals("gettersXMax ", ligne.getCadreMaxX(), ligne.getC2().getAbscisse(), 0.1);
		assertEquals("gettersYMax ", ligne.getCadreMaxY(), ligne.getC2().getOrdonnee(), 0.1);

		assertEquals("gettersXMin ", ligne.getCadreMinX(), ligne.getC1().getAbscisse(), 0.1);
		assertEquals("gettersYMin ", ligne.getCadreMinY(), ligne.getC1().getOrdonnee(), 0.1);
		
		Ligne ligne2 = new Ligne(new Coordonnees(), 1, 1);
		ligne2.setC1(new Coordonnees(2, 2));
		assertEquals("set c1 largeur ", -1, ligne2.getLargeur(), 0.1);
		assertEquals("set c1 hauteur ", -1 , ligne2.getHauteur(), 0.1);
		
		
	}
	@Test
	public void testToString() {
		Ligne ligne = new Ligne(new Coordonnees(), 1, 1);
		assertEquals("renvoie en chaine de caractères", "[Ligne] c1 : (0,0 , 0,0) c2 : (1,0 , 1,0) "
				+ "longueur : 1,41 angle : 45,0° couleur = R51,V51,B51", ligne.toString());
		
		Locale.setDefault(new Locale("en"));
		
		assertEquals("renvoie en chaine de caractères", "[Ligne] c1 : (0.0 , 0.0) c2 : (1.0 , 1.0) "
				+ "longueur : 1.41 angle : 45.0° couleur = R51,G51,B51", ligne.toString());		
		Locale.setDefault( new Locale("fr"));
		
		Ligne ligne2 = new Ligne(new Coordonnees(24, 54), 1, 1);
		ligne2.setC2(new Coordonnees(-52, 8));
		
		assertEquals("renvoie en chaine de caractères", "[Ligne] c1 : (24,0 , 54,0) c2 : (-52,0 , 8,0) "
				+ "longueur : 88,84 angle : 211,18° couleur = R51,V51,B51", ligne2.toString());		
	}
	

	@Test
	public void testCouleur() {
		Ligne ligne = new Ligne(new Coordonnees(), 1, 1);
		ligne.setCouleur(Color.black);
		assertEquals("couleur", Color.black, ligne.getCouleur());
		Ligne ligne2 = new Ligne(new Coordonnees());
		assertEquals("couleur defaut",UIManager.getColor("Panel.foreground"), ligne2.getCouleur());
	}
	@Test
	public void testAire() {
		Ligne ligne = new Ligne(new Coordonnees(), 1, 1);
		assertEquals("renvoie aire", 0, ligne.aire(), 0.1);
	}
	
	@Test
	public void testGetC2CasSpecial() {
		Ligne ligne = new Ligne(new Coordonnees(), 0, 0);
		assertEquals("get C2", 0, ligne.getC2().getAbscisse(), 0.1);
		
	}

}
