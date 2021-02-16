package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;

import java.awt.Color;

import org.junit.Test;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;

public class CercleTestBasesCouleur {
	
	@Test
	public void testConstructeur() {
		Cercle cercle1 = new Cercle(new Coordonnees(1, 1), 2);
		Cercle cercle2 = new Cercle(3);
		Cercle cercle3 = new Cercle(new Coordonnees(1, 1));
		Cercle cercle4 = new Cercle();
		
		assertEquals("cons 1 Mauvais x", 1, cercle1.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 1 Mauvais Y", 1, cercle1.getPosition().getOrdonnee(), 0.1);
		assertEquals("cons 1 Mauvais MaxX", 3, cercle1.getCadreMaxX(), 0.1);
		assertEquals("cons 1 Mauvais MaxY", 3, cercle1.getCadreMaxY(), 0.1);
		
		assertEquals("cons 2 Mauvais x", 0, cercle2.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 2 Mauvais Y", 0, cercle2.getPosition().getOrdonnee(), 0.1);
		assertEquals("cons 2 Mauvais MaxX", 3, cercle2.getCadreMaxX(), 0.1);
		assertEquals("cons 2 Mauvais MaxY", 3, cercle2.getCadreMaxY(), 0.1);

		assertEquals("cons 3 Mauvais x", 1, cercle3.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 3 Mauvais Y", 1, cercle3.getPosition().getOrdonnee(), 0.1);

		assertEquals("cons 4 Mauvais x", 0, cercle4.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 4 Mauvais Y", 0, cercle4.getPosition().getOrdonnee(), 0.1);
	}
	
	@Test
	public void testGetSet() {
		Cercle cercle = new Cercle(2);
		assertEquals("Mauvaise Largeur 2", 2, cercle.getLargeur(), 0.1);
		assertEquals("Mauvaise Hauteur2", 2, cercle.getHauteur(), 0.1);

		cercle.setLargeur(3);
		assertEquals("Mauvaise Largeur 3", 3, cercle.getLargeur(), 0.1);
		assertEquals("Mauvaise Hauteur 3", 3, cercle.getHauteur(), 0.1);
	
		cercle.setHauteur(4);
		assertEquals("Mauvaise Largeur 4", 4, cercle.getLargeur(), 0.1);
		assertEquals("Mauvaise Hauteur 4", 4, cercle.getHauteur(), 0.1);
			
	}
	
	@Test
	public void testDeplacer() {
		Cercle cercle = new Cercle(2);
		cercle.deplacerVers(3, 2);
		
		assertEquals("deplacer Mauvais x", 3, cercle.getPosition().getAbscisse(), 0.1);
		assertEquals("deplacer Mauvais y", 2, cercle.getPosition().getOrdonnee(), 0.1);
		cercle.deplacerDe(-2, -1);
		assertEquals("deplacerDe Mauvais x", 1, cercle.getPosition().getAbscisse(), 0.1);
		assertEquals("deplacerDe Mauvais y", 1, cercle.getPosition().getOrdonnee(), 0.1);
		
	}
	
	@Test
	public void testAirePerim() {
		Cercle cercle =new Cercle(1);
		assertEquals("aire", 0.5*0.5*Forme.PI, cercle.aire(), 0.1);
		assertEquals("preim", 2*Forme.PI*0.5, cercle.perimetre(), 0.1);
		
		cercle.setLargeur(3);
		assertEquals("aire", 1.5*1.5*Forme.PI, cercle.aire(), 0.1);
		assertEquals("perim", 2*Forme.PI*1.5, cercle.perimetre(), 0.1);		
	
		
	}
	@Test
	public void testToString() {
		Cercle cercle =new Cercle(2);
		assertEquals("toString", "[Cercle] : pos (0,0 , 0,0) dim 2,0 x 2,0 périmètre : 6,28 aire : "
				+ "3,14 couleur = R51,V51,B51", cercle.toString());
		cercle.setRempli(true);
		assertEquals("toString", "[Cercle-Rempli] : pos (0,0 , 0,0) dim 2,0 x 2,0 périmètre : 6,28 aire : "
				+ "3,14 couleur = R51,V51,B51", cercle.toString());
		

	}
	
	@Test
	public void testCouleur() {
		Cercle cercle =new Cercle(2);
		cercle.setCouleur(Color.black);
		assertEquals("couleur", Color.black, cercle.getCouleur());

	}
	@Test
	public void testRemplie() {
		Cercle cercle = new Cercle();
		assertEquals("rempli", false, cercle.estRempli());
		cercle.setRempli(true);
		assertEquals("rempli", true, cercle.estRempli());
		
	}
	
}
