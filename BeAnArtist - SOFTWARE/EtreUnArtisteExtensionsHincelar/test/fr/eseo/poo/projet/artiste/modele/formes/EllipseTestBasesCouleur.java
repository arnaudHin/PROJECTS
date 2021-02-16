package fr.eseo.poo.projet.artiste.modele.formes;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import java.awt.Color;
import java.util.Locale;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import fr.eseo.poo.projet.artiste.modele.Coordonnees;


public class EllipseTestBasesCouleur {

	@Test
	public void testConstructeur() {
		Ellipse elli1 = new Ellipse(new Coordonnees(1, 1), 3, 2);
		Ellipse elli2 = new Ellipse(3, 2);
		Ellipse elli3 = new Ellipse(new Coordonnees(1, 1));
		Ellipse elli4 = new Ellipse();

		assertEquals("cons 1 Mauvais x", 1, elli1.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 1 Mauvais Y", 1, elli1.getPosition().getOrdonnee(), 0.1);
		assertEquals("cons 1 Mauvais MaxX", 4, elli1.getCadreMaxX(), 0.1);
		assertEquals("cons 1 Mauvais MaxY", 3, elli1.getCadreMaxY(), 0.1);
		
		assertEquals("cons 2 Mauvais x", 0, elli2.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 2 Mauvais Y", 0, elli2.getPosition().getOrdonnee(), 0.1);
		assertEquals("cons 2 Mauvais MaxX", 3, elli2.getCadreMaxX(), 0.1);
		assertEquals("cons 2 Mauvais MaxY", 2, elli2.getCadreMaxY(), 0.1);

		assertEquals("cons 3 Mauvais x", 1, elli3.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 3 Mauvais Y", 1, elli3.getPosition().getOrdonnee(), 0.1);
		
		assertEquals("cons 4 Mauvais x", 0, elli4.getPosition().getAbscisse(), 0.1);
		assertEquals("cons 4 Mauvais Y", 0, elli4.getPosition().getOrdonnee(), 0.1);
	}
	
	@Test
	public void testDeplacer() {
		Ellipse elli = new Ellipse(1,1);
		elli.deplacerVers(3, 2);
		
		assertEquals("deplacer Mauvais x", 3, elli.getPosition().getAbscisse(), 0.1);
		assertEquals("deplacer Mauvais y", 2, elli.getPosition().getOrdonnee(), 0.1);
		elli.deplacerDe(-2, -1);
		assertEquals("deplacerDe Mauvais x", 1, elli.getPosition().getAbscisse(), 0.1);
		assertEquals("deplacerDe Mauvais y", 1, elli.getPosition().getOrdonnee(), 0.1);			
	}
	
	@Test
	public void testAire() {
		Ellipse elli =new Ellipse(3, 2);
		assertEquals("Aire de l'ellipse", 1.5*Forme.PI, elli.aire(), 0.1);
	}
	@Test
	public void testPerimetre() {
		Ellipse elli =new Ellipse(3, 2);
		double varh = Math.pow(((elli.getHauteur()*0.5-elli.getLargeur()*0.5)/(elli.getHauteur()*0.5+
				elli.getLargeur()*0.5)), 2);
		assertEquals("Perimetre de l'ellipse b > a", Forme.PI*(elli.getHauteur()*0.5+elli.getLargeur()*
				0.5)*(1 + 3*varh/(10
				+Math.sqrt(4-3*varh))), elli.perimetre(), 0.1);
		
		Ellipse elli2 =new Ellipse(2, 3);
		double varh2 = Math.pow(((-elli2.getHauteur()*0.5+elli2.getLargeur()*0.5)/(elli2.getHauteur()*0.5+
				elli2.getLargeur()*0.5)), 2);
		assertEquals("Perimetre de l'ellipse b > a", Forme.PI*(elli2.getHauteur()*0.5+elli2.getLargeur()*
				0.5)*(1 + 3*varh2/(10
				+Math.sqrt(4-3*varh2))), elli2.perimetre(), 0.1);
	}
	
	
	@Test
	public void testToString() {
		Ellipse ell = new Ellipse(2, 2);
		assertEquals("toString non rempli fr", "[Ellipse] : pos (0,0 , 0,0) dim 2,0 x 2,0 périmètre : 6,28 aire :"
				+ " 3,14 couleur = R51,V51,B51", 
				ell.toString());
		ell.setRempli(true);
		assertEquals("toString rempli fr", "[Ellipse-Rempli] : pos (0,0 , 0,0) dim 2,0 x 2,0 périmètre : 6,28 aire :"
				+ " 3,14 couleur = R51,V51,B51", 
				ell.toString());
		ell.setRempli(false);
		Locale.setDefault(new Locale("en"));
		assertEquals("toString non rempli en", "[Ellipse] : pos (0.0 , 0.0) dim 2.0 x 2.0 périmètre : 6.28 aire :"
				+ " 3.14 couleur = R51,G51,B51", 
				ell.toString());	
		Locale.setDefault( new Locale("fr"));

	}
	
	@Test
	public void testCouleur() {
		Ellipse ell = new Ellipse(2, 2);
		ell.setCouleur(Color.black);
		assertEquals("couleur", Color.black, ell.getCouleur());
	}
	
	@Test
	public void testRempli(){
		Ellipse ell = new Ellipse(2, 2);
		assertEquals("non rempli", false, ell.estRempli());
		ell.setRempli(true);
		assertEquals("rempli", true, ell.estRempli());
	}
	@Rule
	public ExpectedException exception = ExpectedException.none();
	@Test
	public void testNegativeLargeur() {
        exception.expect(IllegalArgumentException.class);
		Ellipse ell = new Ellipse(2, 2);
		ell.setLargeur(-3);  
	}
	@Test
	public void testNegativeHauteur() {
        exception.expect(IllegalArgumentException.class);
		Ellipse ell = new Ellipse(2, 2);
		ell.setHauteur(-3);  
	}	
	@Test
	public void testSetters() {
		Ellipse ell = new Ellipse(2, 2);
		ell.setLargeur(3);
		assertEquals("setLargeur", 3, ell.getC2().getAbscisse() , 0.1);
	}
	
	
}
